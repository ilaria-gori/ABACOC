CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJECTNAME ABACOC)
PROJECT(${PROJECTNAME})

ADD_DEFINITIONS(-std=c++0x)

if(NOT DEFINED ENV{EIGEN_ROOT})
message(FATAL_ERROR "Could not find EIGEN_ROOT environment variable")
endif()

include_directories("$ENV{EIGEN_ROOT}")

set(folder_header include/ball.h include/searcher.h include/ballPredictor.h include/model.h include/exhaustiveSearcher.h include/maxBallPredictor.h include/utility.h include/parameters.h include/randomGenerator.h include/distance.h)
set(folder_source src/main.cpp src/ball.cpp src/model.cpp src/exhaustiveSearcher.cpp src/maxBallPredictor.cpp src/utility.cpp src/parameters.cpp src/randomGenerator.cpp src/distance.cpp)

if (WIN32)
	set(folder_header ${folder_header} include/windows/dirent.h)
endif ()

source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECTNAME} ${folder_source} ${folder_header} )
