#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <map>
#include <vector>
#include "dirent.h"

namespace abacoc
{
	//class Searcher;
	typedef std::vector<double> Sample;
	enum norm_t{NONE, L1, L2};

	struct Video
	{
		int class_id;
		std::string alias;
		std::vector<Sample> samples;
	};

	struct Parameters
	{
		int n_classes;
		int mod_size;
		int intr_dimension;
	};

	std::vector<Video> readDataset(const std::map<std::string, std::string> &args);

	Parameters readParameters(const std::map<std::string, std::string> &args);

	std::map<std::string, std::string> parseLine(int argc, char* argv[]);

	int str2int(const std::string &s);

	void normalizeData(std::vector<Video> &dataset, norm_t norm_type);

	void addDerivative(std::vector<Video> &dataset, norm_t norm_type);
}

#endif