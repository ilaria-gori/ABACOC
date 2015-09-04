#include <algorithm>
#include <fstream>
#include <iostream>
#include "model.h"
#include "utility.h"
#include "exhaustiveSearcher.h"
#include "maxBallPredictor.h"
#include "randomGenerator.h"

using namespace abacoc;

std::vector<MatlabModel> readFromFile(const std::string &matFile)
{
	std::vector<MatlabModel> models;
	std::ifstream myfile(matFile);
	std::string line;
	while (std::getline(myfile, line))
	{
		MatlabModel m;
		std::vector<int> err;
		std::istringstream iss(line);
		std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), std::back_inserter(err));
		m.errors = err;

		std::getline(myfile, line);
		std::vector<int> n_x_s;
		std::istringstream iss1(line);
		std::copy(std::istream_iterator<int>(iss1), std::istream_iterator<int>(), std::back_inserter(n_x_s));
		m.n_x_s = n_x_s;

		std::getline(myfile, line);
		std::vector<int> n_centre_up;
		std::istringstream iss2(line);
		std::copy(std::istream_iterator<int>(iss2), std::istream_iterator<int>(), std::back_inserter(n_centre_up));
		m.n_centre_upd = n_centre_up;

		std::getline(myfile, line);
		std::vector<double> eps_b;
		std::istringstream iss3(line);
		std::copy(std::istream_iterator<double>(iss3), std::istream_iterator<double>(), std::back_inserter(eps_b));
		m.eps_b = eps_b;

		std::getline(myfile, line);
		std::vector<double> eps_start;
		std::istringstream iss4(line);
		std::copy(std::istream_iterator<double>(iss4), std::istream_iterator<double>(), std::back_inserter(eps_start));
		m.eps_start = eps_start;

		models.push_back(m);
	}

	myfile.close();
	return models;
}

int main(int argc, char* argv[])
{
	std::map<std::string, std::string> line_args;

	if (argc > 1)
	{
		line_args = parseLine(argc, argv);
	}

	//this reads the dataset in a convenient format (each class folder contains files with features as
	//lines of doubles) and, if requested by the user, normalize them and/or add the derivative. You can
	//use the same function twice to get train and test and using "-train" and "-test" as second parameter
	Dataset train = readDataset(line_args, "-train");
	if (train.empty())
	{
		std::cout << "Error while reading dataset" << std::endl;
		return 0;
	}

	Dataset test = readDataset(line_args, "-test");
	if (test.empty())
	{
		std::cout << "Error while reading dataset" << std::endl;
		return 0;
	}

	Parameters parameters(line_args);

	//You can implement your own Searcher. 
	//Right now, we support ExhaustiveSearcher and KDTreeSearcher.
	Searcher* searcher;
	std::map<std::string, std::string>::const_iterator it;
	it = line_args.find("-s");
	if (it != line_args.end())
	{
		std::string search_type = it->second;
		if (strcmp(search_type.c_str(), "kdtree") == 0)
		{
			;
		}
		else if (strcmp(search_type.c_str(), "ex"))
		{
			searcher = new ExhaustiveSearcher(&parameters);
		}
	}
	else
	{
		searcher = new ExhaustiveSearcher(&parameters);
	}

	//You can implement your own ballPredictor.
	//Right now we support MaxBallPredictor.
	BallPredictor* ball_pred;
	it = line_args.find("-p");
	if (it != line_args.end())
	{
		std::string pred_type = it->second;
		if (strcmp(pred_type.c_str(), "max") == 0)
		{
			ball_pred = new MaxBallPredictor();
		}
	}
	else
	{
		ball_pred = new MaxBallPredictor();
	}

	std::string matlab_file = "C:\\Users\\Ilaria\\Desktop\\matlab.txt";
	std::vector<MatlabModel> models_to_compare = readFromFile(matlab_file);
	Model model(&parameters, searcher, ball_pred);
	/*RandomGenerator rand_gen(train.size());
	
	for (size_t i = 0; i < train.size(); i++)
	{
		int rand_ind = rand_gen.getNext();
		model.train(train[rand_ind]);
	}*/

	FooGenerator foo_gen(train.size(), 9);
	for (size_t i = 0; i < train.size(); i++)
	{
		int rand_ind = foo_gen.getNext();
		model.train(train[rand_ind]);
		printf("iter %d\n", i);
		if (!model.compareOutput(models_to_compare[i]))
		{
			break;
		}
	}

	//This is to save the model into a .txt file
	std::string out = "C:\\Users\\Ilaria\\Desktop\\output.txt";
	model.save(out);

	return 0;
}