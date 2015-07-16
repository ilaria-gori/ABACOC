#ifndef _MAX_BALL_PREDICTOR_H_
#define _MAX_BALL_PREDICTOR_H_

#include "ballPredictor.h"

namespace abacoc
{
	class MaxBallPredictor : public BallPredictor
	{
		bool predict(const Ball &ball, const Sample &sample);
	};
}

#endif
