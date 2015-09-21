#include "model.h"

namespace abacoc
{
	Model::Model(const Parameters* parameters) : parameters(parameters), searcher(nullptr), ball_predictor(nullptr)
	{
		init_sample.class_id = -1;
		searcher = new ExhaustiveSearcher(parameters);
		ball_predictor = new MaxBallPredictor();
	}

	Model::Model(const Parameters* parameters, Searcher* searcher, BallPredictor* ball_predictor) : parameters(parameters), searcher(searcher), ball_predictor(ball_predictor)
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
					Ball ball(0, sample, init_radius);
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
			if (distance < ball->radius)
			{
				ball->update(s, ball_predictor, *parameters);
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
				maxval = max(0, distance - ball->radius);
			#else
				maxval = std::max(0, distance - ball->radius);
			#endif
			double exp_value = maxval*maxval;
			double den = 2 * ball->radius*ball->radius;

			double kernel_weight = exp(- (exp_value / den));
			VectorE class_probs = VectorE::Zero(classes.size());

			for (auto it = ball->class_samples.begin(); it != ball->class_samples.end(); it++)
			{
				class_probs(it->first) = (double)it->second / (double)ball->tot_samples;
			}

			class_scores += class_probs;
			weighted_probs += (class_probs*kernel_weight);
			sum_weights += kernel_weight;
		}

		VectorE class_confidence = weighted_probs/data.samples.size();

		int index = -1;
		double max_val = 0.0;
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

}