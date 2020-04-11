#pragma once

#include "ConnectorListNode.h"

class ConnectorList
{
private:
	ConnectorListNode* firstNode;
	ConnectorListNode* lastNode;
	int size;

public:
	ConnectorList(Connector* connectors[] = { });
	~ConnectorList();
};

