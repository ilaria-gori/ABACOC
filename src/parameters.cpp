#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "parameters.h"
#include "utility.h"

namespace abacoc
{
	Parameters::Parameters() : n_classes(0), mod_size(INT_MAX), intr_dimension(2)
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

		int n_classes = 0;
		it = line_args.find("-n_c");
		if (it != line_args.end())
		{
			int tmp = str2int(it->second);
			if (tmp != -1)
				n_classes = tmp;
		}

		int m_size = INT_MAX;
		it = line_args.find("-m");
		if (it != line_args.end())
		{
			int tmp = str2int(it->second);
			if (tmp != -1)
				m_size = tmp;
		}

		this->n_classes = n_classes;
		this->intr_dimension = intr_dim;
		this->mod_size = m_size;
	}
}

