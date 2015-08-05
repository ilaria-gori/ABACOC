#ifndef _RANDOM_GENERATOR_H_
#define _RANDOM_GENERATOR_H_

#include <vector>
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
}

#endif