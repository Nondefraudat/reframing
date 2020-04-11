
#include "ConnectorList.h"

ConnectorList::ConnectorList(Connector* connectors[]) {
	firstNode = lastNode = new ConnectorListNode(nullptr);
	size = sizeof(connectors) / sizeof(Connector);
	for (int i = 0; i < size; i++) {
		lastNode->setNextNode(new ConnectorListNode(connectors[i]));
		lastNode = lastNode->getNextNode();
	}
}

ConnectorList::~ConnectorList() {

}
