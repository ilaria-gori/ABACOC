#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <map>
#include <vector>
#include "distance.h"

namespace abacoc
{
	struct Parameters
	{
		unsigned int mod_size;
		int intr_dimension;
		Distance* distance;
		int distance_exp;
		pred_type prediction_type;

		Parameters();
		Parameters(const std::map<std::string, std::string> &line_args);
		~Parameters();
	};
}

#endif