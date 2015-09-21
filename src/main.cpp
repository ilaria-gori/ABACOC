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
	//Command line args are saved in the following map and are used to initialize the 
	//Parameters data structure
	std::map<std::string, std::string> line_args;

	if (argc > 1)
	{
		line_args = parseLine(argc, argv);
	}

	//This reads the dataset in a convenient format and, if requested by the user, 
	//normalize them and/or add the derivative. You can
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
	//Right now, we support ExhaustiveSearcher.
	Searcher* searcher;
	std::map<std::string, std::string>::const_iterator it;
	it = line_args.find("-s");
	if (it == line_args.end())
	{
		searcher = new ExhaustiveSearcher(&parameters);
	}

	//You can implement your own ballPredictor.
	//Right now we support MaxBallPredictor.
	BallPredictor* ball_pred;
	it = line_args.find("-p");
	if (it == line_args.end())
	{
		ball_pred = new MaxBallPredictor();
	}

	Model model(&parameters, searcher, ball_pred);

	/*RandomGenerator rand_gen(train.size());
	
	for (size_t i = 0; i < train.size(); i++)
	{
		int rand_ind = rand_gen.getNext();
		model.train(train[rand_ind]);
	}*/

	SequentialGenerator seq_gen(train.size(), 9);
	for (size_t i = 0; i < train.size(); i++)
	{
		int rand_ind = seq_gen.getNext();
		model.train(train[rand_ind]);
	}

	int correct_pred = 0;
	for (size_t i = 0; i < test.size(); i++)
	{
		double confidence = 0;
		int class_id = model.predict(test[i], confidence);

		if (class_id == test[i].class_id)
		{
			correct_pred += 1;
		}
	}

	double accuracy = (double)correct_pred / (double)test.size();
	std::cout << "Accuracy = " << accuracy << std::endl;
	return 0;
}