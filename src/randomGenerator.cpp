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

#include <numeric>
#include <assert.h>
#include "randomGenerator.h"

using namespace abacoc;

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

SequentialGenerator::SequentialGenerator(int ind_max, int n_classes) : n_classes(n_classes)
{
	if (ind_max <= 0)
	{
		printf("Empty set\n");
		assert(ind_max > 0);
	}
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

int SequentialGenerator::getNext()
{
	int ind = indexes[0];
	indexes.pop_front();
	return ind;
}

