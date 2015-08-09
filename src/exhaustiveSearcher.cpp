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
		std::transform(balls.begin(), balls.end(), prob.begin(), [](Ball b) ->double {return (double)b.errors; });
		double totProb = (double)(std::accumulate(prob.begin(), prob.end(), 0.0) + balls.size());
		std::transform(prob.begin(), prob.end(), prob.begin(),
			[totProb](double val) -> double 
			{return (val+1) / totProb; });
		
		std::vector<int> indexes = sortIndexesDesc(prob);
		double partialSum = 0;
		std::transform(prob.begin(), prob.end(), prob.begin(),
			[&partialSum](double val) -> double
			{partialSum += val;
			return partialSum; });

		double random = randUniform(0.0, 1.0);
		for (auto el : indexes)
		{
			if (random < prob[el])
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