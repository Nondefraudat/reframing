#pragma once

#include <list>

#include "GameObject.h"
#include "ActionResults.h"
#include "OperationsList.h"
#include "ConnectionTypes.h"

using namespace std;

class Connector;

class FunctionalObject :
	public GameObject
{
protected:
	list<Connector*>* connectors;

public:
	FunctionalObject(int width, int height);
	FunctionalObject(int x, int y, int width, int height);

	list<Connector*>* getConnectors();

	void setConnectors(list<Connector*>* connectors);

	virtual int action(int& itemTag, int& operation) = 0;
};

class Connector
{
	int xOffset;
	int yOffset;
	int connectionType;
	FunctionalObject* callback;
	Connector* link;

public:
	Connector(int xOffset, int yOffset, FunctionalObject* callback);
	~Connector();

	int getXOffset();
	int getYOffset();
	int getConnectionType();
	FunctionalObject* getCallback();
	Connector* getLink();
	
	void setCallback(FunctionalObject* callback);
	void setLink(Connector* link = nullptr);
};
