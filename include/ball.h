#ifndef _BALL_H_
#define _BALL_H_

#include <iostream>
#include <fstream>
#include <set>
#include "utility.h"
#include "parameters.h"

namespace abacoc
{
	class BallPredictor;

	struct Ball
	{
		long ID;
		std::map<int, int> class_samples;
		int tot_samples;
		int errors;
		int n_updates;
		double init_radius;
		double radius;

		Ball(const long ID, const Sample &center, double radius);
		void update(const Sample &sample, const BallPredictor* ball_predictor, const Parameters &par);
		VectorE getCenter() const;
		void printBall() const;
		void saveBall(std::ofstream &file) const;

	private:
		VectorE center;

		void updateCenter();
	};
}

#endif