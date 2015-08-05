#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <map>
#include <vector>
#include "dirent.h"

namespace abacoc
{
	struct Parameters
	{
		int n_classes;
		int mod_size;
		int intr_dimension;

		Parameters();
		Parameters(const std::map<std::string, std::string> &line_args);
	};
}

#endif