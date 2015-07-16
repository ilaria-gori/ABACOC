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

		Ball(const std::vector<double> &center, double radius, int n_classes);
		void update(const Sample &sample, const BallPredictor* ball_predictor);
		std::vector<double> getCenter();

	private:
		std::vector<double> center;

		void shrinkRadius();
		void updateRadius();
		void updateCenter();
	};
}

#endif