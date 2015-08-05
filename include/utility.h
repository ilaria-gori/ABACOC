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

	template<typename T>
	void swap(std::vector<T> &data, int i, int j)
	{
		T tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}

	typedef std::vector<Video> Dataset;

	Dataset readDataset(const std::map<std::string, std::string> &args, const std::string &file);

	std::map<std::string, std::string> parseLine(int argc, char* argv[]);

	int str2int(const std::string &s);

	double str2double(const std::string &s);

	void normalizeData(std::vector<Video> &dataset, norm_t norm_type);

	void addDerivative(std::vector<Video> &dataset, norm_t norm_type);
}

#endif