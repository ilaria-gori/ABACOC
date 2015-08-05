#include <algorithm>
#include <fstream>
#include <iostream>
#include "model.h"
#include "utility.h"
#include "exhaustiveSearcher.h"
#include "maxBallPredictor.h"
#include "randomGenerator.h"

using namespace abacoc;

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

	//You can implement your own Searcher. 
	//Right now, we support ExhaustiveSearcher and KDTreeSearcher.
	Searcher* searcher;
	Searcher::distance_t dis = Searcher::EUCL;
	std::map<std::string, std::string>::const_iterator it;
	it = line_args.find("-dis");
	if (it != line_args.end())
	{
		std::string d_type = it->second;
		if (strcmp(d_type.c_str(), "eucl") == 0)
		{
			dis = Searcher::EUCL;
		}
	}

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
			searcher = new ExhaustiveSearcher(dis);
		}
	}
	else
	{
		searcher = new ExhaustiveSearcher(dis);
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

	Parameters parameters(line_args);
	Model model(parameters, searcher, ball_pred);
	RandomGenerator rand_gen(train.size());
	
	for (size_t i = 0; i < train.size(); i++)
	{
		int rand_ind = rand_gen.getNext();
		model.train(train[rand_ind]);
	}

	return 0;
}