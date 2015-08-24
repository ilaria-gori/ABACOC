#ifndef _MODEL_H_
#define _MODEL_H_

#include <set>
#include "ball.h"
#include "maxBallPredictor.h"
#include "parameters.h"
#include "utility.h"
#include "exhaustiveSearcher.h"

namespace abacoc
{
	class Model
	{
		std::set<int> classes;
		BallPredictor* ball_predictor;
		Searcher* searcher;
		const Parameters* parameters;

		double computeConfidence(const Sample &sample) const;
		double computeInitRadius(const VectorE &sample1, const VectorE &sample2) const;

	public:
		Model(const Parameters* parameters);
		Model(const Parameters* parameters, Searcher* searcher, BallPredictor* ball_predictor);
		~Model();
		void train(const Video &video);
		void predict(const Video &video, int &class_id, double &confidence);
		void save(const std::string &file) const;
	};
}

#endif