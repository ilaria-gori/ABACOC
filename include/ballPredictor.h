#ifndef _BALL_PREDICTOR_H_
#define _BALL_PREDICTOR_H_

#include "utility.h"

namespace abacoc
{
	class Ball;

	class BallPredictor
	{
	public:
		virtual bool predict(const Ball &ball, const Sample &sample) const = 0;
	};
}

#endif