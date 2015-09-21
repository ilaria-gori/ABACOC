#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <map>
#include <vector>
#include <deque>
#include <numeric>
#include <random>
#include <iostream>
#include <valarray>
#include <Eigen/Dense>

#ifdef _WIN32
	#include "windows/dirent.h"
#else
	#include "dirent.h"
#endif

namespace abacoc
{
	typedef Eigen::VectorXd VectorE;
	const double eps = 0.0000000001;
	enum norm_t{NONE, L1, L2};
	enum pred_type{CONFIDENCE, SCORE};

	struct Data
	{
		int class_id;
		std::string alias;
		std::deque<VectorE> samples;
	};

	typedef std::vector<Data> Dataset;

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

	double randUniform(double lower, double upper);

	Dataset readDataset(const std::map<std::string, std::string> &args, const std::string &file);

	Dataset readFolder(const std::string &path);

	bool readClassFile(const std::string &class_path, const std::string &class_alias, int class_id, Dataset &dataset);

	std::map<std::string, std::string> parseLine(int argc, char* argv[]);

	int str2int(const std::string &s);

	double str2double(const std::string &s);

	VectorE vect2eigen(const std::vector<double> &v);

	std::vector<double> eigen2vect(const VectorE &v);

	void normalizeData(Dataset &dataset, norm_t norm_type);

	void addDerivative(Dataset &dataset, norm_t norm_type);
}

#endif