#ifndef _RANDOM_GENERATOR_H_
#define _RANDOM_GENERATOR_H_

#include <vector>
#include <deque>
#include "utility.h"

namespace abacoc
{
	class RandomGenerator
	{
		std::vector<int> indexes;

	public:
		RandomGenerator(int ind_max);
		int getNext();
	};

	class SequentialGenerator
	{
		std::deque<int> indexes;
		int n_classes;

	public:
		SequentialGenerator(int ind_max, int n_classes);
		int getNext();
	};
}

#endif