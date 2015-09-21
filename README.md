# ABACOC

A C++ library for incremental, nonparametric classification.

Author: Ilaria Gori, Rocco De Rosa
email: ilary.gori@gmail.com, rocco.derosa@unimi.it

## References
For Multivariate Time Series Classification:
Rocco De Rosa, Nicolò Cesa-Bianchi, Ilaria Gori and Fabio Cuzzolin (2014), "Online Action Recognition via Nonparametric Incremental Learning". BMVC 2014.

For Standard Classification:
Rocco De Rosa, Francesco Orabona and Nicolò Cesa-Bianchi (2015), "The ABACOC Algorithm: a Novel Approach for Nonparametric Classification of Data Streams". Proc.The 2015 IEEE 15th International Conference on Data Mining (ICDM'15).

## Installation
The only dependence is Eigen. Download Eigen and create an environment variable called EIGEN_ROOT, which points to the Eigen folder.
The program has been tested under both Linux and Windows. In both cases, we use cmake.

## Brief tutorial
The objects to create are, in order:

##### Dataset
We provide a simple program to read a set of feature vectors from file. In our setting, there is one file for each class. Each file contains a feature vector on each line. The feature vectors belonging to the same data structure (set of features extracted from a video, or set of features extracted from an image) are separated by a newline. Different sets of feature vectors are separated by a set of white spaces. In general, the Dataset data structure is a vector of Data, where Data contains the class name to whom it belongs, a unique class_id and a set of feature vectors. We also provide a method to normalize the data and to add derivative information (in case you are working on time series) while reading the dataset. Normalization can be enabled using the command line arg -n, and can be L1 or L2. Derivative can be enabled using the command line arg -t.

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