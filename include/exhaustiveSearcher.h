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

#ifndef _EXHAUSTIVE_SEARCHER_H
#define _EXHAUSTIVE_SEARCHER_H

#include <valarray>
#include <limits>
#include "searcher.h"

namespace abacoc
{
	class ExhaustiveSearcher : public Searcher
	{
		std::vector<Ball> balls;
		std::valarray<double> prob;

	public:

		ExhaustiveSearcher(const Parameters* parameters);
		Ball* knnsearch(const Sample &sample, double &distance);
		void addBall(const Ball &ball);
		void removeBall(const Ball &ball);
		long getNumBall() const;
		void printBalls() const;
		void saveBalls(const std::string &file) const;
		std::vector<Ball> getBalls() const;
		~ExhaustiveSearcher();

	protected:
		int findBallToRemove();
	};
}

#endif