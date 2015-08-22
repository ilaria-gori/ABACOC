#include "maxBallPredictor.h"
#include "ball.h"

namespace abacoc
{
	bool MaxBallPredictor::predict(const Ball &ball, const Sample &sample) const
	{
		return (find(ball.winning_class.begin(), ball.winning_class.end(), sample.class_id) != ball.winning_class.end());
	}
}

