#include "Base.h"

Base::Base(double alpha, long distance, int width, int height, ConnectorList ports, ConnectorList sockets)
	: Part(width, height, ports, sockets)
{
	this->alpha = alpha;
	this->distance = distance;
}

Base::~Base() {

}

double Base::getAlpha() {
	return alpha;
}

long Base::getDistance()
{
	return distance;
}
