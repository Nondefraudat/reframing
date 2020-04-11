#include "Part.h"

Part::Part(int width, int height, ConnectorList ports, ConnectorList sockets) {
	this->width = width;
	this->height = height;
	this->ports = ports;
	this->sockets = sockets;
}

Part::~Part() {

}

int Part::getWidth() {
	return width;
}

int Part::getHeight() {
	return height;
}

ConnectorList Part::getPorts() {
	return ports;
}

ConnectorList Part::getSockets()
{
	return sockets;
}

