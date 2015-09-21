#include "maxBallPredictor.h"
#include "ball.h"

namespace abacoc
{
	bool MaxBallPredictor::predict(const Ball &ball, const Sample &sample) const
	{
		int max = 0;
		int index = -1;
		for_each(ball.class_samples.cbegin(), ball.class_samples.cend(), [&max, &index](std::pair<const int,int> class_sample)
			{ if (class_sample.second > max) { max = class_sample.second; index = class_sample.first; } });

		return sample.class_id == index;
	}
}

