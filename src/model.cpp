#include "model.h"

namespace abacoc
{
	Model::Model(const Parameters* parameters) : parameters(parameters), searcher(nullptr), ball_predictor(nullptr)
	{
		searcher = new ExhaustiveSearcher(parameters);
		ball_predictor = new MaxBallPredictor();
	}

	Model::Model(const Parameters* parameters, Searcher* searcher, BallPredictor* ball_predictor) : parameters(parameters), searcher(searcher), ball_predictor(ball_predictor)
	{
	}

	void Model::train(const Video &video)
	{
		int iter = 0;
		classes.insert(video.class_id);
		if (searcher->getNumBall() == 0)
		{
			VectorE s = video.samples[0];
			double init_radius = computeInitRadius(s, video.samples[1]);
			Sample sample(video.class_id, s);
			Ball ball(0, sample, init_radius);
			searcher->addBall(ball);
			iter = 1;
		}
		for (size_t i = iter; i < video.samples.size(); i++)
		{
			//std::cout << video.samples[i] << std::endl;
			double distance = 0;
			Sample s(video.class_id, video.samples[i]);
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

	bool Model::compareOutput(const MatlabModel &m) const
	{
		for (int i = 0; i < searcher->getNumBall(); i++)
		{
			Ball b = searcher->getBalls()[i];
			if (b.errors != m.errors[i] || b.n_updates != m.n_centre_upd[i] || b.tot_samples != m.n_x_s[i] || (b.init_radius-m.eps_start[i])>0.001 || (b.radius-m.eps_b[i])>0.001)
			{
				return false;
			}
		}
		return true;
	}
}