#ifndef _EXHAUSTIVE_SEARCHER_H
#define _EXHAUSTIVE_SEARCHER_H

#include <valarray>
#include "searcher.h"

namespace abacoc
{
	class ExhaustiveSearcher : public Searcher
	{
		std::vector<Ball> balls;
		std::valarray<double> prob;

	public:

		ExhaustiveSearcher(const Parameters &parameters);
		Ball* knnsearch(const Sample &sample, double &distance) const;
		void addBall(const Ball &ball);
		void removeBall(const Ball &ball);
		int getNumBall() const;
		~ExhaustiveSearcher();

	protected:
		int findBallToRemove();
	};
}

#endif