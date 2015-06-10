cmake_minimum_required(VERSION 2.8)
set(PROJECTNAME ABACOC2.0)
project(${PROJECTNAME})

set(headers include/classifier.h
	include/ABACOCClassifier.h
	include/dirent.h
	include/trainingParameters.h)
set(sources src/ABACOCClassifier.cpp
	src/main.cpp)
	
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories("$ENV{EIGEN3_INCLUDE_DIR}")
	
source_group("Source Files" FILES ${sources})
source_group("Header Files" FILES ${headers})

add_executable(${PROJECTNAME} ${sources} ${headers})
