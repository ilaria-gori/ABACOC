#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include "utility.h"

namespace abacoc
{
	std::map<std::string, std::string> parseLine(int argc, char* argv[])
	{
		std::map<std::string, std::string> line_args;

		for (int i = 1; i < argc; i = i + 2)
		{
			char* key = argv[i];
			if (i + 1 < argc)
			{
				char* val = argv[i + 1];
				line_args[std::string(key)] = std::string(val);
			}
		}

		return line_args;
	}

	int str2int(const std::string &s)
	{
		std::stringstream ss(s);
		int res;
		ss >> res;
		return (ss.fail()) ? -1 : res;
	}

	double str2double(const std::string &s)
	{
		std::stringstream ss(s);
		double res;
		ss >> res;
		return (ss.fail()) ? -1 : res;
	}

	double randUniform(double lower, double upper)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(lower, upper);
		return dis(gen);
	}

	VectorE vect2eigen(const std::vector<double> &v)
	{
		VectorE sample(v.size());
		for (size_t i = 0; i < v.size(); i++)
		{
			sample(i) = v[i];
		}
		return sample;
	}

	std::vector<double> eigen2vect(const VectorE &v)
	{
		std::vector<double> sample(v.size());
		for (auto i = 0; i < v.size(); i++)
		{
			sample[i] = v(i);
		}
		return sample;
	}

	bool readClassFile(const std::string &class_path, const std::string &class_alias, int class_id, Dataset &dataset)
	{
		Data data;
		data.alias = class_alias;
		data.class_id = class_id;

		std::ifstream file(class_path.c_str());
		std::string line;
		std::deque<VectorE> features;
		getline(file, line);
		while (file)
		{
			getline(file, line);
			std::stringstream string_line(line);
			std::vector<double> v;

			if (line.find_first_not_of(' ') != std::string::npos)
			{
				while (string_line.good())
				{
					std::string substr;
					getline(string_line, substr, ' ');
					v.push_back(str2double(substr));
				}
			}

			if (v.empty())
			{
				data.samples = features;
				dataset.push_back(data);
				features.clear();
			}
			else
			{
				VectorE sample = vect2eigen(v);
				features.push_back(sample);
			}
		}
		return true;
	}

	Dataset readFolder(const std::string &path)
	{
		Dataset dataset;

		struct dirent *class_folder;
		DIR *dataset_folder;

		dataset_folder = opendir(path.c_str());
		if (dataset_folder == NULL)
		{
			dataset.clear();
			return dataset;
		}

		while ((class_folder = readdir(dataset_folder)))
		{
			if (strcmp(class_folder->d_name, ".") == 0 || strcmp(class_folder->d_name, "..") == 0)
				continue;
			else
				break;
		}

		bool done = false;
		bool init = true;
		int class_id = 0;
		while (!done)
		{
			std::string class_name;
			if (init)
			{
				if (class_folder->d_name != NULL)
					class_name = class_folder->d_name;

				init = false;
			}
			else
			{
				if (!(class_folder = readdir(dataset_folder)))
				{
					done = true;
					break;
				}
				class_name = class_folder->d_name;
			}

			if (!readClassFile(path + "/" + class_name, class_name, class_id, dataset))
			{
				dataset.clear();
				return dataset;
			}
			class_id += 1;
		}
		return dataset;
	}

	Dataset readDataset(const std::map<std::string, std::string> &line_args, const std::string &file)
	{
		Dataset dataset;

		std::map<std::string, std::string>::const_iterator it;
		std::string path = "";
		it = line_args.find(file);
		if (it != line_args.end())
		{
			path = it->second;
		}
		else
		{
			std::cout << "Please provide a dataset file" << std::endl;
			return dataset;
		}

		dataset = readFolder(path);

		bool normalize_data = false;
		norm_t norm_type = NONE;
		it = line_args.find("-n");
		if ((it != line_args.end()))
		{
			normalize_data = true;
			if (it->second == "L1")
			{
				norm_type = L1;
			}
			else if (it->second == "L2")
			{
				norm_type = L2;
			}
		}

		bool add_derivative = false;
		it = line_args.find("-t");
		if ((it != line_args.end()))
		{
			add_derivative = true;
		}

		if (add_derivative)
		{
			addDerivative(dataset, norm_type);
		}

		if (normalize_data)
		{
			normalizeData(dataset, norm_type);
		}

		return dataset;
	}

	void normalizeData(Dataset &dataset, norm_t norm_type)
	{
		for (size_t i = 0; i < dataset.size(); i++)
		{
			Data& data = dataset[i];
			std::for_each(begin(data.samples), end(data.samples), [](VectorE &vect) { vect /= vect.norm(); });
		}
	}

	void addDerivative(Dataset &dataset, norm_t norm_type)
	{
		if (norm_type != NONE)
		{
			normalizeData(dataset, norm_type);
		}

		for (size_t i = 0; i < dataset.size(); i++)
		{
			Data& data = dataset[i];

			for (size_t i = data.samples.size() - 1; i > 0; i--)
			{
				VectorE diff = data.samples[i] - data.samples[i - 1];
				VectorE joined_vectors(data.samples[i].size() * 2);
				joined_vectors << data.samples[i], diff;
				data.samples[i] = joined_vectors;
			}

			data.samples.pop_front();
		}
	}
}

