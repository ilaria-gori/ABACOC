#include "exhaustiveSearcher.h"

namespace abacoc
{
	ExhaustiveSearcher::ExhaustiveSearcher(const Parameters &parameters) : Searcher(parameters)
	{
		balls.reserve(parameters.mod_size);
		if (parameters.mod_size != INT_MAX)
		{
			prob.resize(parameters.mod_size, 0.0);
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

	int ExhaustiveSearcher::findBallToRemove()
	{
		std::transform(balls.begin(), balls.end(), std::begin(prob), [](Ball b) ->double {return (double)b.errors; });
		prob = (prob + 1.0) / (prob.sum() + balls.size());
		
		std::vector<int> indexes = sortIndexesDesc(prob);
		std::valarray<double> sums(prob);
		std::partial_sum(std::begin(prob), std::end(prob), std::begin(sums));

		double random = randUniform(0.0, 1.0);
		for (auto el : indexes)
		{
			if (random < sums[el])
			{
				return el;
			}
		}

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