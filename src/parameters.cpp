#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "parameters.h"
#include "utility.h"

namespace abacoc
{
	Parameters::Parameters() : mod_size(INT_MAX), intr_dimension(2), distance(nullptr), distance_exp(2)
	{

	}

	Parameters::Parameters(const std::map<std::string, std::string> &line_args)
	{
		std::map<std::string, std::string>::const_iterator it;
		int intr_dim = 2;
		it = line_args.find("-dim");
		if (it != line_args.end())
		{
			int tmp = str2int(it->second);
			if (tmp != -1)
				intr_dim = tmp;
		}

		int m_size = INT_MAX;
		it = line_args.find("-msize");
		if (it != line_args.end())
		{
			int tmp = str2int(it->second);
			if (tmp != -1)
				m_size = tmp;
		}

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
				distance = new EuclDistance();
			}
			else if (strcmp(d_type.c_str(), "mink") == 0)
			{
				distance = new MinkDistance(distance_exp);
			}
		}

		this->intr_dimension = intr_dim;
		this->mod_size = m_size;
	}

	Parameters::~Parameters()
	{
		delete distance;
	}
}


