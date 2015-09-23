#include "ball.h"
#include "ballPredictor.h"

using namespace abacoc;

Ball::Ball(const long ID, const Sample &center, double radius) : ID(ID), tot_samples(1), errors(0), n_updates(1), init_radius(radius), radius(radius), center(center.v)
{
	class_samples[center.class_id] = 1;
}

void Ball::update(const Sample &sample, const BallPredictor &ball_predictor, const Parameters &par)
{
	tot_samples += 1;
	if ((class_samples).find(sample.class_id) == class_samples.end())
	{
		class_samples[sample.class_id] = 0;
	}
	class_samples[sample.class_id] += 1;

	if (ball_predictor.predict(*this, sample))
	{
		n_updates += 1;
		VectorE delta = sample.v - center;
		center += delta / n_updates;
	}
	else
	{
		errors += 1;
		radius = init_radius * pow((double)errors, -1.0 / (2 + par.intr_dimension));
	}
}

VectorE Ball::getCenter() const
{
	return center;
}

void Ball::printBall() const
{
	std::cout << "ID " << ID << " tot_samples " << tot_samples << " errors " << errors << " n_updates " << n_updates << " init_radius " << init_radius << " radius " << radius << std::endl;
	std::cout << "class_samples ";
	for_each(class_samples.cbegin(), class_samples.cend(), [](std::pair<int, int> p) {std::cout << p.first << " " << p.second << " "; });
	std::cout << std::endl;
}

void Ball::saveBall(std::ofstream &file) const
{
	file << "ID " << ID << " tot_samples " << tot_samples << " errors " << errors << " n_updates " << n_updates << " init_radius " << init_radius << " radius " << radius << std::endl;
	file << "class_samples ";
	for_each(class_samples.cbegin(), class_samples.cend(), [&file](std::pair<int, int> p) {file << p.first << " " << p.second << " "; });
	file << std::endl;
}

