#ifndef _EXHAUSTIVE_SEARCHER_H
#define _EXHAUSTIVE_SEARCHER_H

#include "searcher.h"

namespace abacoc
{
	class ExhaustiveSearcher : public Searcher
	{
		std::vector<Ball> balls;
		Eigen::VectorXd p;

	public:
		ExhaustiveSearcher(const Parameters &parameters);
		Ball* knnsearch(const Sample &sample, double &distance) const;
		void addBall(const Ball &ball);
		void removeBall(const Ball &ball);
		int getNumBall() const;
		~ExhaustiveSearcher();

	protected:
		int findBallToRemove() const;
	};
}

#endif