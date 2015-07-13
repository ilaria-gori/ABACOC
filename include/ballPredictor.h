#ifndef _BALL_PREDICTOR_H_
#define _BALL_PREDICTOR_H_

#include <vector>

struct Ball;

typedef std::vector<double> Sample;

class BallPredictor
{
	virtual bool predict(const Ball &ball, const Sample &sample) = 0;
};

#endif