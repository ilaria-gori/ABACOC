#include <algorithm>
#include "model.h"
#include "exhaustiveSearcher.h"

int main(int argc, char* argv[])
{
	int intr_dim = 2;
	/*if(cmdOptionExists(argv, argv+argc, "-f"))
    {
        char* f = getCmdOption(argv, argv + argc, "-f");
		intr_dim = atoi(f);
    }*/

	Parameters parameters;
	parameters.n_classes = 0;
	parameters.intr_dimension = intr_dim;
	parameters.mod_size = INT_MAX;

	Searcher* searcher;
	BallPredictor* ball_pred;

	Searcher::distance_t dis = Searcher::EUCL;
	/*if(cmdOptionExists(argv, argv+argc, "-d"))
    {
        char* d = getCmdOption(argv, argv + argc, "-d");
		distance = atoi(d);
    }

	if(cmdOptionExists(argv, argv+argc, "-s"))
    {
        char* d = getCmdOption(argv, argv + argc, "-s");
		distance = atoi(d);
    }
	else
	{*/
		searcher = new ExhaustiveSearcher(dis);
	//}



	return 0;
}