#ifndef _MODEL_H_
#define _MODEL_H_

#include "searcher.h"
#include "ball.h"
#include "ballPredictor.h"
#include "parameters.h"
#include "utility.h"

namespace abacoc
{
	class Model
	{
		std::vector<Ball> balls;
		BallPredictor* ball_predictor;
		Searcher* searcher;
		Parameters parameters;

		double computeConfidence(const Sample &sample) const;

	public:
		Model(const Parameters &parameters);
		Model(const Parameters &parameters, Searcher* searcher, BallPredictor* ball_predictor);
		~Model() {};
		void train(const Video &sample);
		void predict(const Video &sample, int &class_id, double &confidence);
	};
}

#endif