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

	bool readClassFolder(const std::string &class_path, const std::string &class_alias, int class_id, std::vector<Video> &dataset)
	{
		struct dirent *video_file;
		DIR *class_folder;

		class_folder = opendir(class_path.c_str());
		if (class_folder == NULL)
		{
			return false;
		}

		while ((video_file = readdir(class_folder)))
		{
			if (strcmp(video_file->d_name, ".") == 0 || strcmp(video_file->d_name, "..") == 0)
				continue;
			else
				break;
		}

		bool done = false;
		bool init = true;
		while (!done)
		{
			Video video;
			video.alias = class_alias;
			video.class_id = class_id;

			std::string video_name;
			if (init)
			{
				if (video_file->d_name != NULL)
					video_name = video_file->d_name;

				init = false;
			}
			else
			{
				if (!(video_file = readdir(class_folder)))
				{
					done = true;
					break;
				}
				video_name = video_file->d_name;
			}

			std::ifstream file(video_name.c_str());
			std::string line;
			std::vector<Sample> features;
			while (file)
			{
				getline(file, line);
				std::stringstream string_line(line);
				Sample sample;

				//split the line based on spaces
				copy(std::istream_iterator<double>(string_line),
					std::istream_iterator<double>(),
					std::back_inserter(sample));

				features.push_back(sample);
			}
			video.samples = features;
			dataset.push_back(video);
		}
		return true;
	}

	std::vector<Video> readFolders(const std::string &path)
	{
		std::vector<Video> dataset;

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

			if (!readClassFolder(path + "/" + class_name, class_name, class_id, dataset))
			{
				dataset.clear();
				return dataset;
			}
			class_id += 1;
		}
		return dataset;
	}

	std::vector<Video> readDataset(const std::map<std::string, std::string> &line_args)
	{
		std::vector<Video> dataset;

		std::map<std::string, std::string>::const_iterator it;
		std::string path = "";
		it = line_args.find("-file");
		if (it != line_args.end())
		{
			path = it->second;
		}
		else
		{
			std::cout << "Please provide a dataset file" << std::endl;
			return dataset;
		}

		dataset = readFolders(path);

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

		if (normalize_data)
		{
			normalizeData(dataset, norm_type);
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

		return dataset;
	}

	Parameters readParameters(const std::map<std::string, std::string> &line_args)
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

		Parameters parameters;
		parameters.n_classes = n_classes;
		parameters.intr_dimension = intr_dim;
		parameters.mod_size = m_size;

		return parameters;
	}

	void normalizeData(std::vector<Video> &dataset, norm_t norm_type)
	{
		
	}

	void addDerivative(std::vector<Video> &dataset, norm_t norm_type)
	{

	}
}

