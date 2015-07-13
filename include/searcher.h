#ifndef _SEARCHER_H_
#define _SEARCHER_H_

#include "ball.h"

typedef std::vector<double> Sample;

class Searcher
{

public:
	enum distance_t {EUCL};
	Searcher(distance_t distance) : distance(distance) {}
	virtual void knnsearch(const Sample &sample, int &ballID, double &distance) const = 0;	
	virtual void addBall(const Ball &ball) = 0;
	virtual void removeBall(const Ball &ball) = 0;
	virtual ~Searcher() {}

private:
	distance_t distance;

};

#endif