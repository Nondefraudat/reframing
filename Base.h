#pragma once

#include "Part.h"

class Base 
	: Part 
{
private:
	double alpha;
	long distance;

public:
	Base(double alpha, long distance, int width, int height, ConnectorList ports, ConnectorList sockets);
	~Base();

	double getAlpha();
	long getDistance();
};

