#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "parameters.h"
#include "utility.h"

namespace abacoc
{
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

		this->prediction_type = CONFIDENCE;
		it = line_args.find("-p");
		if (it != line_args.end())
		{
			int tmp = str2int(it->second);
			if (tmp == 1)
			{
				this->prediction_type = SCORE;
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
}


