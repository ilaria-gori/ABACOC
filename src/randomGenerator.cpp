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

	FooGenerator::FooGenerator(int ind_max, int n_classes) : n_classes(n_classes)
	{
		indexes.resize(ind_max);
		int n_ex_per_class = ind_max / n_classes;
		int iter = 0;
		for (int i = 0; i < n_ex_per_class; i++)
		{
			for (int j = 0; j < n_classes; j++)
			{
				indexes[iter++] = i + (j*n_ex_per_class);
			}
		}
	}

	int FooGenerator::getNext()
	{
		int ind = indexes[0];
		indexes.pop_front();
		return ind;
	}
}
