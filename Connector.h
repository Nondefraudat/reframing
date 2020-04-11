#pragma once

#include "Part.h"

class Connector
{
private:
	int x;
	int y;
	Part* part;

public:
	Connector(int x, int y, Part* part = nullptr);
	~Connector();

	int getX();
	int getY();
	Part* getPart();


};

