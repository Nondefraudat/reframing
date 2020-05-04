#include "FunctionalObject.h"

FunctionalObject::FunctionalObject(int width, int height) : FunctionalObject(0, 0, width, height)
{

}

FunctionalObject::FunctionalObject(int x, int y, int width, int height) : GameObject(x, y, width, height)
{
	connectors = nullptr;
}

list<Connector*>* FunctionalObject::getConnectors()
{
	return connectors;
}

void FunctionalObject::setConnectors(list<Connector*>* connectors)
{
	this->connectors = connectors;
}

int FunctionalObject::action(int& itemTag, int& operation)
{
	return AR_UNKNOWNOPERATION;
}

Connector::Connector(int xOffset, int yOffset, FunctionalObject* callback)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	connectionType = CT_DEFAULT;
	this->callback = callback;
	link = nullptr;
}

Connector::~Connector()
{

}

int Connector::getXOffset()
{
	return xOffset;
}

int Connector::getYOffset()
{
	return yOffset;
}

int Connector::getConnectionType()
{
	return connectionType;
}

FunctionalObject* Connector::getCallback()
{
	return callback;
}

Connector* Connector::getLink()
{
	return link;
}

void Connector::setCallback(FunctionalObject* callback)
{
	this->callback = callback;
}

void Connector::setLink(Connector* link)
{
	if (link)
	{
		this->link = link;
		link->link = this;
	}
	else 
	{
		if (this->link)
		{
			this->link->link = link;
			this->link = link;
		}
	}
}
