#include "Battery.h"

Battery::Battery(int charge, int maxCharge, int width, int height, ConnectorList ports, ConnectorList sockets)
	: Part(width, height, ports, sockets) 
{
	this->charge = charge;
	this->maxCharge = maxCharge;
}

Battery::~Battery() {

}

int Battery::getCharge() {
	return charge;
}

void Battery::setCharge(int charge) {
	this->charge = charge;
}
