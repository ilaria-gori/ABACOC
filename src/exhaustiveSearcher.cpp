#include "exhaustiveSearcher.h"

namespace abacoc
{
	ExhaustiveSearcher::ExhaustiveSearcher(const Parameters* parameters) : Searcher(parameters)
	{
		if (parameters->mod_size != INT_MAX)
		{
			balls.reserve(parameters->mod_size);
			prob.resize(parameters->mod_size, 0.0);
		}
	}

	Ball* ExhaustiveSearcher::knnsearch(const Sample &sample, double &distance)
	{
		Ball* closest = nullptr;
		double min_distance = std::numeric_limits<double>::infinity();
		int min_index = 0;

		for (size_t i = 0; i < balls.size(); i++)
		{
			double dist = parameters->distance->computeDistance(balls[i].getCenter(), sample.v);
			if (dist < min_distance)
			{
				min_distance = dist;
				min_index = i;
			}
		}
		distance = min_distance;
		return &balls[min_index];
	}

	void ExhaustiveSearcher::addBall(const Ball &ball)
	{
		if (balls.size() < parameters->mod_size || parameters->mod_size == INT_MAX)
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

	long ExhaustiveSearcher::getNumBall() const
	{
		return (long)balls.size();
	}

	void ExhaustiveSearcher::removeBall(const Ball &ball)
	{
	}

	ExhaustiveSearcher::~ExhaustiveSearcher()
	{

	}

	void ExhaustiveSearcher::printBalls() const
	{
		for_each(balls.begin(), balls.end(), [](Ball b) {b.printBall(); });
	}

	void ExhaustiveSearcher::saveBalls(const std::string &file) const
	{
		std::ofstream output(file);
		for_each(balls.begin(), balls.end(), [&output](Ball b) {b.saveBall(output); });
		output.close();
	}

	std::vector<Ball> ExhaustiveSearcher::getBalls() const
	{
		return balls;
	}
}