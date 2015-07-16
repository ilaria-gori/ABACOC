#ifndef _EXHAUSTIVE_SEARCHER_H
#define _EXHAUSTIVE_SEARCHER_H

#include "searcher.h"

namespace abacoc
{
	class ExhaustiveSearcher : public Searcher
	{

	public:
		ExhaustiveSearcher(distance_t distance);
		void knnsearch(const Sample &sample, int &ballID, double &distance) const;
		void addBall(const Ball &ball);
		void removeBall(const Ball &ball);
		~ExhaustiveSearcher();
	};
}

#endif