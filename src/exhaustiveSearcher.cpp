/* Copyright: (C) 2015 Ilaria Gori, All rights reserved
* Author: Ilaria Gori
* email: ilary.gori@gmail.com
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The views and conclusions contained in the software and documentation are those
* of the authors and should not be interpreted as representing official policies,
* either expressed or implied, of the FreeBSD Project.
*/

#include "exhaustiveSearcher.h"

using namespace abacoc;

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
	std::transform(balls.begin(), balls.end(), std::begin(prob), [](Ball b) ->double {return (double)b.getErrors(); });
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
	for_each(balls.cbegin(), balls.cend(), [](Ball b) {b.printBall(); });
}

void ExhaustiveSearcher::saveBalls(const std::string &file) const
{
	std::ofstream output(file);
	for_each(balls.cbegin(), balls.cend(), [&output](Ball b) {b.saveBall(output); });
	output.close();
}

std::vector<Ball> ExhaustiveSearcher::getBalls() const
{
	return balls;
}

