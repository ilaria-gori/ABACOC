# Tutorial

A brief tutorial on ABACOC usage.

## Installation
The only dependence is Eigen. Download Eigen and create an environment variable called EIGEN_ROOT, which points to the Eigen folder. Then, download ABACOC using git: 

    git clone https://github.com/ilaria-gori/ABACOC
	
then we compile using cmake. In Linux:

	mkdir build
	cd build
	ccmake ..
	make
	
In Windows this program has been tested using CmakeGui and Visual Studio.

## Code
The objects to create are, in order:

##### Dataset
We provide a simple program to read a set of feature vectors from file. In our setting, there is one file for each class. Each file contains a feature vector on each line. The feature vectors belonging to the same data structure (set of features extracted from a video, or set of features extracted from an image) are separated by a newline. Different sets of feature vectors are separated by a set of white spaces. For example, imagine that we have a set of videos belonging to the class "run", and that for each video we extract a set of feature vectors. The file "run.txt" will look like this:

	0.2 -0.8 0.5 0.4
	0.33 0.28 -0.9 0.11
	0.28 -0.42 0.54 0.9
	
	0.44 -0.12 -0.88 0.9
	0.24 0.56 0.72 0.60
	0.33 0.29 0.9 -0.11
	0.52 0.2 -0.1 0.009
	
The first three lines correspond to the three feature vectors extracted from the first video. The remaining four lines represent the four feature vectors extracted from the second video. We also provide a method to normalize the data and to add derivative information (in case you are working on time series) while reading the dataset. Normalization can be enabled using the command line arg -n, and can be L1 or L2. Derivative can be enabled using the command line arg -t.

In general, the program expects a Dataset, which is a vector of Data, where Data contains the class name to whom it belongs, a unique class_id and a set of feature vectors. 

##### Parameters
The Parameters data structure is initialized using the map structure created reading the command line. It contains:
- mod_size, "-msize" in the command line, max number of balls in the model. The default is infinite.
- intr_dimension, "-dim" in the command line, used to shrink the radius of the balls when there are errors. The default is 2.
- prediction_type, "-p" in the command line. It can be score (0) or confidence (1). The default is score.
- distance, "-dis" in the command line. It can be Euclidean ("eucl") or Minkowski ("mink"). The default is Euclidean. 
- distance_exp, "-dis_exp" in the command line. If used the Minkowski distance is used, this represents the exponent. The default is 2.

##### Searcher
This is the structure that contains the balls and their information. Right now, the Exhaustive Searcher is supported, but it is possible to implement your customized version of a searcher. 

##### BallPredictor
This is the class that takes care of indicating whether a ball predicted the right class or not. Right now, the Max Ball Predictor is supported, but it is possible to implement your customized version.

##### Model
At this point, the model can be initialized. It needs a pointer to the parameters, a pointer to the searcher and a pointer to the ball predictor.

##### Index Generator
For the incremental training, we provide two Generator classes (RandomGenerator and SequentialGenerator), which choose what sample has to be fed to the classifier next. The SequentialGenerator picks a sample for each class.

## Example
A complete example can be found in the main.cpp file. The dataset used is jvowels, provided in the format accepted by our readDataset function. To run the example using all the default parameters, you can run: ABACOC -train "path_of_where_you_put_jvowels\train" -test "path_of_where_you_put_jvowels\test".