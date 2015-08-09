#include "distance.h"

namespace abacoc
{
	double MinkDistance::computeDistance(const VectorE &v1, const VectorE &v2) const
	{
		VectorE diffAbs = (v1-v2).cwiseAbs();
		VectorE pow = diffAbs;
		for (int i = 0; i < exponent-1; i++)
		{
			pow = pow*diffAbs;
		}
		double sum = pow.sum();
		double exp = 1.0 / (double)exponent;
		return pow(sum, exp);
	}

	double EuclDistance::computeDistance(const VectorE &v1, const VectorE &v2) const
	{
		return (v1 - v2).norm();
	}
}
