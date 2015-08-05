#include <numeric>
#include <assert.h>
#include "randomGenerator.h"

namespace abacoc
{
	RandomGenerator::RandomGenerator(int ind_max)
	{
		if (ind_max <= 0)
		{
			printf("Empty set\n");
			assert(ind_max > 0);
		}
		indexes.resize(ind_max);
		std::iota(indexes.begin(), indexes.end(), 0);
	}

	int RandomGenerator::getNext()
	{
		int rand_ind = rand() % indexes.size();
		int rand_num = indexes[rand_ind];
		swap(indexes, rand_ind, indexes.size() - 1);
		indexes.pop_back();
		return rand_num;
	}

}
