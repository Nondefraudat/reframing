#pragma once

#include "Part.h"

class Battery
	: Part
{
private:
	int charge;
	int maxCharge;

public:
	Battery(int charge, int maxCharge, int width, int height, ConnectorList ports, ConnectorList sockets);
	~Battery();

	int getCharge();
	void setCharge(int charge);
};

