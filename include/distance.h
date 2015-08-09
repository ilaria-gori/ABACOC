#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "utility.h"

namespace abacoc
{
	class Distance
	{
	public:
		virtual double computeDistance(const VectorE &v1, const VectorE &v2) const = 0;
	};

	class MinkDistance : public Distance
	{
		int exponent;

	public:
		MinkDistance(int exponent) : exponent(exponent) {}
		double computeDistance(const VectorE &v1, const VectorE &v2) const;
	};

	class EuclDistance : public Distance
	{
	public:
		double computeDistance(const VectorE &v1, const VectorE &v2) const;
	};
}

#endif