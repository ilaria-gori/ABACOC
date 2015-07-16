#ifndef _BALL_PREDICTOR_H_
#define _BALL_PREDICTOR_H_

#include "utility.h"

namespace abacoc
{
	struct Ball;

	class BallPredictor
	{
		virtual bool predict(const Ball &ball, const Sample &sample) = 0;
	};
}

#endif