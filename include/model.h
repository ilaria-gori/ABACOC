#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include "searcher.h"
#include "ball.h"
#include "ballPredictor.h"

typedef std::vector<double> Sample;

struct Parameters
{
	int n_classes;
	int mod_size;
	int intr_dimension;
};

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
	~Model();
	void train(const Sample &sample);
	void predict(const Sample &sample, int &class_id, double &confidence);
};

#endif