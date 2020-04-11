#pragma once

#include "Connector.h"

class ConnectorListNode
{
private:
	Connector* connector;
	ConnectorListNode* nextNode;
public:
	ConnectorListNode(Connector* connector);
	~ConnectorListNode();

	Connector* getConnector();
	void setConnector(Connector* connector);
	ConnectorListNode* getNextNode();
	void setNextNode(ConnectorListNode* nextNode);
};

