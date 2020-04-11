#pragma once

#include "Part.h"

class Engine 
	: Part 
{
private:
	int power;

public:
	Engine(int power, int width, int height, ConnectorList ports, ConnectorList sockets);
	~Engine();


};

