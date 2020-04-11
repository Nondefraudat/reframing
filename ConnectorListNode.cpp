#include "ConnectorListNode.h"

ConnectorListNode::ConnectorListNode(Connector* connector) {
	this->connector = connector;
	this->nextNode = nullptr;
}

ConnectorListNode::~ConnectorListNode() {
}

Connector* ConnectorListNode::getConnector() {
	return connector;
}

void ConnectorListNode::setConnector(Connector* connector) {
	this->connector = connector;
}

ConnectorListNode* ConnectorListNode::getNextNode() {
	return nextNode;
}

void ConnectorListNode::setNextNode(ConnectorListNode* nextNode) {
	this->nextNode = nextNode;
}
