#include "exhaustiveSearcher.h"

namespace abacoc
{
	ExhaustiveSearcher::ExhaustiveSearcher(const Parameters &parameters) : Searcher(parameters)
	{
		balls.reserve(parameters.mod_size);
		if (parameters.mod_size != INT_MAX)
		{
			p.resize(parameters.mod_size, 0);
		}
	}

	Ball* ExhaustiveSearcher::knnsearch(const Sample &sample, double &distance) const
	{
		return nullptr;
	}

	void ExhaustiveSearcher::addBall(const Ball &ball)
	{
		if (balls.size() < parameters.mod_size || parameters.mod_size == INT_MAX)
		{
			balls.push_back(ball);
		}
		else
		{
			int index = findBallToRemove();
			balls[index] = ball;
		}
	}

	int ExhaustiveSearcher::findBallToRemove() const
	{
		//std::transform(balls.begin(), balls.end(), std::begin(p), [](Ball b) ->double {return (double)b.errors; });
		return 0;
	}

	int ExhaustiveSearcher::getNumBall() const
	{
		return balls.size();
	}

	void ExhaustiveSearcher::removeBall(const Ball &ball)
	{
	}

	ExhaustiveSearcher::~ExhaustiveSearcher()
	{

	}
}