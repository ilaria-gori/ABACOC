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

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "parameters.h"
#include "utility.h"

using namespace abacoc;

Parameters::Parameters() : mod_size(INT_MAX), intr_dimension(2), distance(nullptr), distance_exp(2), prediction_type(CONFIDENCE)
{
	distance = new EuclDistance();
}

Parameters::Parameters(const std::map<std::string, std::string> &line_args)
{
	std::map<std::string, std::string>::const_iterator it;
	this->mod_size = INT_MAX;
	it = line_args.find("-msize");
	if (it != line_args.end())
	{
		int tmp = str2int(it->second);
		if (tmp != -1)
		{
			this->mod_size = tmp;
		}
	}

	this->intr_dimension = 2;
	it = line_args.find("-dim");
	if (it != line_args.end())
	{
		int tmp = str2int(it->second);
		if (tmp != -1)
			this->intr_dimension = tmp;
	}

	this->prediction_type = SCORE;
	it = line_args.find("-p");
	if (it != line_args.end())
	{
		int tmp = str2int(it->second);
		if (tmp == 1)
		{
			this->prediction_type = CONFIDENCE;
		}
	}

	this->distance_exp = 2;
	it = line_args.find("-dis_exp");
	if (it != line_args.end())
	{
		int tmp = str2int(it->second);
		if (tmp != -1 && tmp > 0)
		{
			this->distance_exp = tmp;
		}
		else
		{
			printf("The exponent for the Minkowski distance must be greater than 0. Using the default (2)\n");
		}
	}

	it = line_args.find("-dis");
	if (it != line_args.end())
	{
		std::string d_type = it->second;
		if (strcmp(d_type.c_str(), "eucl") == 0)
		{
			this->distance = new EuclDistance();
		}
		else if (strcmp(d_type.c_str(), "mink") == 0)
		{
			this->distance = new MinkDistance(distance_exp);
		}
	}
	else
	{
		this->distance = new EuclDistance();
	}
}

Parameters::~Parameters()
{
	if (distance != nullptr)
	{
		delete distance;
		distance = nullptr;
	}
}


