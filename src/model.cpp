#include "model.h"

namespace abacoc
{
	Model::Model(const Parameters &parameters) : parameters(parameters)
	{
	}

	Model::Model(const Parameters &parameters, Searcher* searcher, BallPredictor* ball_predictor) : parameters(parameters), searcher(searcher), ball_predictor(ball_predictor)
	{
	}

}