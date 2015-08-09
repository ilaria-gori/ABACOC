#ifndef _BALL_H_
#define _BALL_H_

#include "utility.h"

namespace abacoc
{
	class BallPredictor;

	struct Ball
	{
		long ID;
		std::map<int, int> class_samples;
		int tot_samples;
		int errors;
		double init_radius;
		double radius;

		Ball(const long ID, const Sample &center, double radius);
		void update(const Sample &sample, const BallPredictor* ball_predictor);
		VectorE getCenter() const;

	private:
		VectorE center;

		void shrinkRadius();
		void updateRadius();
		void updateCenter();
	};
}

#endif