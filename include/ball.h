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

#ifndef _BALL_H_
#define _BALL_H_

#include <iostream>
#include <fstream>
#include <set>
#include "utility.h"
#include "parameters.h"
#include "ballPredictor.h"

namespace abacoc
{
	class Ball
	{
		long ID;
		std::map<int, int> class_samples;
		int tot_samples;
		int errors;
		int n_updates;
		double init_radius;
		double radius;
		VectorE center;

		void updateCenter();

	public:
		Ball(const long ID, const Sample &center, double radius);
		void update(const Sample &sample, const BallPredictor &ball_predictor, const Parameters &par);
		long getID() const;
		std::map<int, int> getClassSamples() const;
		int getTotSamples() const;
		int getErrors() const;
		int getNumUpdates() const;
		double getInitRadius() const;
		double getRadius() const;
		VectorE getCenter() const;

		void printBall() const;
		void saveBall(std::ofstream &file) const;
	};
}

#endif