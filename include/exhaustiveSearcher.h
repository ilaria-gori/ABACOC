#ifndef _EXHAUSTIVE_SEARCHER_H
#define _EXHAUSTIVE_SEARCHER_H

#include <valarray>
#include <limits>
#include "searcher.h"

namespace abacoc
{
	class ExhaustiveSearcher : public Searcher
	{
		std::vector<Ball> balls;
		std::valarray<double> prob;

	public:

		ExhaustiveSearcher(const Parameters* parameters);
		Ball* knnsearch(const Sample &sample, double &distance);
		void addBall(const Ball &ball);
		void removeBall(const Ball &ball);
		long getNumBall() const;
		void printBalls() const;
		void saveBalls(const std::string &file) const;
		std::vector<Ball> getBalls() const;
		~ExhaustiveSearcher();

	protected:
		int findBallToRemove();
	};
}

#endif