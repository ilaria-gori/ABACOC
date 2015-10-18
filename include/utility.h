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