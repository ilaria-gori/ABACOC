#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <map>
#include <vector>
#include <numeric>
#include <random>
#include <iostream>
#include <valarray>
#include <Eigen/Dense>
#include "dirent.h"

namespace abacoc
{
	//class Searcher;
	typedef Eigen::VectorXd VectorE;
	const double eps = 0.0000000001;
	enum norm_t{NONE, L1, L2};

	struct Video
	{
		int class_id;
		std::string alias;
		std::vector<VectorE> samples;
	};

	struct Sample
	{
		int class_id;
		VectorE v;

		Sample() {};
		Sample(int class_id, const VectorE &v) : class_id(class_id), v(v) {}
	};

	template<typename T>
	void swap(std::vector<T> &data, int i, int j)
	{
		T tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}

	double randUniform(double lower, double upper);

	template<typename T>
	std::vector<int> sortIndexesDesc(const std::valarray<T> v)
	{
		std::vector<int> idx(v.size());
		std::iota(idx.begin(), idx.end(), 0);

		std::sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v[i1] > v[i2]; });

		return idx;
	}

	template<typename T>
	std::vector<int> sortIndexesAsc(const std::valarray<T> v)
	{
		std::vector<int> idx(v.size());
		std::iota(idx.begin(), idx.end(), 0);

		std::sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

		return idx;
	}

	template<typename T>
	std::vector<int> sortIndexesDesc(const std::vector<T> &v)
	{
		std::vector<int> idx(v.size());
		std::iota(idx.begin(), idx.end(), 0);

		std::sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v[i1] > v[i2]; });

		return idx;
	}

	template<typename T>
	std::vector<int> sortIndexesAsc(const std::vector<T> &v)
	{
		std::vector<int> idx(v.size());
		std::iota(idx.begin(), idx.end(), 0);

		std::sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

		return idx;
	}

	/*std::vector<int> sortIndexesDesc(const VectorE &v)
	{
		std::vector<int> idx(v.size());
		std::iota(idx.begin(), idx.end(), 0);

		std::sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v(i1) > v(i2); });

		return idx;
	}

	std::vector<int> sortIndexesAsc(const VectorE &v)
	{
		std::vector<int> idx(v.size());
		std::iota(idx.begin(), idx.end(), 0);

		std::sort(idx.begin(), idx.end(),
			[&v](size_t i1, size_t i2) {return v(i1) < v(i2); });

		return idx;
	}*/

	typedef std::vector<Video> Dataset;

	Dataset readDataset(const std::map<std::string, std::string> &args, const std::string &file);

	std::map<std::string, std::string> parseLine(int argc, char* argv[]);

	int str2int(const std::string &s);

	double str2double(const std::string &s);

	VectorE vect2eigen(const std::vector<double> &v);

	void normalizeData(std::vector<Video> &dataset, norm_t norm_type);

	void addDerivative(std::vector<Video> &dataset, norm_t norm_type);
}

#endif