/* Copyright: (C) 2015 Ilaria Gori, All rights reserved
* Author: Ilaria Gori
* email: ilary.gori@gmail.com
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The views and conclusions contained in the software and documentation are those
* of the authors and should not be interpreted as representing official policies,
* either expressed or implied, of the FreeBSD Project.
*/

#include "model.h"

using namespace abacoc;

Model::Model(const Parameters &parameters) : searcher(nullptr), ball_predictor(nullptr)
{
	this->parameters = &parameters;
	init_sample.class_id = -1;
	searcher = new ExhaustiveSearcher(&parameters);
	ball_predictor = new MaxBallPredictor();
}

Model::Model(const Parameters &parameters, Searcher* searcher, BallPredictor* ball_predictor) : parameters(&parameters), searcher(searcher), ball_predictor(ball_predictor)
{
}

void Model::train(const Data &data)
{
	int iter = 0;
	classes.insert(data.class_id);
	if (searcher->getNumBall() == 0)
	{
		VectorE s = data.samples[0];
		if (data.samples.size() > 1)
		{
			double init_radius = computeInitRadius(s, data.samples[1]);
			Sample sample(data.class_id, s);
			Ball ball(0, sample, init_radius);
			searcher->addBall(ball);
			iter = 1;
		}
		else
		{
			if (init_sample.class_id == -1)
			{
				init_sample = Sample(data.class_id, s);
				return;
			}
			else
			{
				double init_radius = computeInitRadius(init_sample.v, data.samples[0]);
				searcher->addBall(Ball(searcher->getNumBall(), init_sample, init_radius));
				Sample sample(data.class_id, data.samples[0]);
				Ball ball(searcher->getNumBall(), sample, init_radius);
				searcher->addBall(ball);
				return;
			}
		}
	}
	for (size_t i = iter; i < data.samples.size(); i++)
	{
		double distance = 0;
		Sample s(data.class_id, data.samples[i]);
		Ball* ball = searcher->knnsearch(s, distance);
		//the sample is in the ball
		if (distance < ball->getRadius())
		{
			ball->update(s, *ball_predictor, *parameters);
		}
		else
		{
			double init_radius = computeInitRadius(s.v, ball->getCenter());
			Ball new_ball(searcher->getNumBall(), s, init_radius);
			searcher->addBall(new_ball);
		}
	}
}

int Model::predict(const Data &data, double &confidence) const
{
	VectorE class_scores = VectorE::Zero(classes.size());
	VectorE weighted_probs = VectorE::Zero(classes.size());
	double sum_weights = 0;

	for (size_t i = 0; i < data.samples.size(); i++)
	{
		double distance = 0;
		Sample s(data.class_id, data.samples[i]);
		Ball* ball = searcher->knnsearch(s, distance);

		double maxval;
		#ifdef _WIN32
			maxval = max(0.0, distance - ball->getRadius());
		#else
			maxval = std::max(0.0, distance - ball->getRadius());
		#endif
		double exp_value = maxval*maxval;
		double den = 2 * ball->getRadius()*ball->getRadius();

		double kernel_weight = exp(- (exp_value / den));
		VectorE class_probs = VectorE::Zero(classes.size());

		std::map<int, int> class_samples = ball->getClassSamples();
		for (auto it = class_samples.cbegin(); it != class_samples.cend(); it++)
		{
			class_probs(it->first) = (double)it->second / (double)ball->getTotSamples();
		}

		class_scores += class_probs;
		weighted_probs += (class_probs*kernel_weight);
		sum_weights += kernel_weight;
	}

	VectorE class_confidence = weighted_probs/data.samples.size();

	int index = -1;
	double max_val = -std::numeric_limits<double>::infinity();
	if (parameters->prediction_type == CONFIDENCE)
	{
		for (auto i = 0; i < class_confidence.size(); i++)
		{
			if (class_confidence(i) > max_val)
			{
				max_val = class_confidence(i);
				index = i;
			}
		}
	}
	else
	{
		for (auto i = 0; i < class_scores.size(); i++)
		{
			if (class_scores(i) > max_val)
			{
				max_val = class_scores(i);
				index = i;
			}
		}
	}

	confidence = class_confidence(index);
	return index;
}

double Model::computeInitRadius(const VectorE &sample1, const VectorE &sample2) const
{
	return parameters->distance->computeDistance(sample1, sample2);
}

Model::~Model()
{
	delete searcher;
	delete ball_predictor;
}

void Model::save(const std::string &file) const
{
	searcher->saveBalls(file);
}
