#ifndef _SEARCHER_H_
#define _SEARCHER_H_

#include "ball.h"
#include "parameters.h"
#include "utility.h"

namespace abacoc
{
	class Searcher
	{

	public:
		Searcher(const Parameters &parameters) : parameters(parameters) {}
		virtual Ball* knnsearch(const Sample &sample, double &distance) const = 0;
		virtual void addBall(const Ball &ball) = 0;
		virtual void removeBall(const Ball &ball) = 0;
		virtual int getNumBall() const = 0;
		virtual ~Searcher() {}

	protected:
		Parameters parameters;

		virtual int findBallToRemove() const = 0;
	};
}

#endif