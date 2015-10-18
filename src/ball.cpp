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

long Ball::getID() const
{
	return ID;
}

std::map<int, int> Ball::getClassSamples() const
{
	return class_samples;
}

int Ball::getTotSamples() const
{
	return tot_samples;
}

int Ball::getErrors() const
{
	return errors;
}

int Ball::getNumUpdates() const
{
	return n_updates;
}

double Ball::getInitRadius() const
{
	return init_radius;
}

double Ball::getRadius() const
{
	return radius;
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

