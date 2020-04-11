#include "Connector.h"

Connector::Connector(int x, int y, Part* part) {
	this->x = x;
	this->y = y;
	this->part = part;
}

Connector::~Connector() {

}

int Connector::getX() {
	return x;
}

int Connector::getY() {
	return y;
}

Part* Connector::getPart() {
	return part;
}