#include "ball.h"

namespace abacoc
{
	Ball::Ball(const long ID, const Sample &center, double radius) : ID(ID), tot_samples(1), errors(0), center(center.v), init_radius(radius), radius(radius)
	{
		class_samples[center.class_id] = 1;
	}

	VectorE Ball::getCenter() const
	{
		return center;
	}
}
