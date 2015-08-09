#include "model.h"

namespace abacoc
{
	Model::Model(const Parameters &parameters) : parameters(parameters), searcher(nullptr), ball_predictor(nullptr)
	{
		searcher = new ExhaustiveSearcher(parameters);
		ball_predictor = new MaxBallPredictor();
	}

	Model::Model(const Parameters &parameters, Searcher* searcher, BallPredictor* ball_predictor) : parameters(parameters), searcher(searcher), ball_predictor(ball_predictor)
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

		}
	}

	double Model::computeInitRadius(const VectorE &sample1, const VectorE &sample2) const
	{
		return parameters.distance->computeDistance(sample1, sample2);
	}

	Model::~Model()
	{
		delete searcher;
		delete ball_predictor;
	}
}