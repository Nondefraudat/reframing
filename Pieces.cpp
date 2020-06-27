#include "Pieces.h"

// ----------------- 
// Frame class block
// -----------------

// Frame constructors\destructors

Frame::Frame(const char** title, const char** description, int windowWidth, int windowHeight, double gravityMult) :
	Entity(title, description)
{
	this->identifier = 0;
	firstPart = lastPart = new Node<Part>(nullptr);

	reverse = false;
	stat = 0;
	phase = 1;

	this->gravityMult = gravityMult;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

// Frame getters

int Frame::getIdentifier()
{
	return identifier;
}
Node<Part>* Frame::getFirstNode()
{
	return firstPart;
}
Node<Part>* Frame::getLastNode()
{
	return lastPart;
}

// Frame setters

void Frame::setIdentifier(int identifier)
{
	this->identifier = identifier;
}
void Frame::setFirstNode(Node<Part>* firstPart)
{
	this->firstPart = firstPart;
}
void Frame::setLastNode(Node<Part>* lastPart)
{
	this->lastPart = lastPart;
}

// Frame methods

void Frame::addPart(Part* part)
{
	lastPart->next = new Node<Part>(part);
	lastPart->next->prev = lastPart;
	lastPart = lastPart->next;
}
void Frame::removePart(Part* part)
{
	Node<Part>* currentNode = firstPart;
	while (currentNode->next and currentNode->value != part)
	{
		currentNode = currentNode->next;
	}
	if (currentNode->value == part)
	{
		currentNode->prev->next = currentNode->next;
		if (currentNode->next)
		{
			currentNode->next->prev = currentNode->prev;
		}
		delete(currentNode);
	}
}

void Frame::showAll()
{
	Node<Part>* currentNode = firstPart;
	while (currentNode->next)
	{
		currentNode = currentNode->next;
		currentNode->value->show(phase, reverse);
	}
}
Part* Frame::diffusion(Node<Frame>* firstFrame)
{
	Node<Part>* currentNode = this->firstPart;
	while (currentNode->next)
	{
		currentNode = currentNode->next;
		Node<Frame>* currentFrame = firstFrame;
		while (currentFrame->next)
		{
			currentFrame = currentFrame->next;
			if (currentFrame->value != this)
			{
				Node<Part>* currentPart = currentFrame->value->firstPart;
				while (currentPart->next)
				{
					currentPart = currentPart->next;
					if (currentNode->value->diffusion(currentPart->value))
					{
						return currentPart->value;
					}
				}
			}
		}
	}
	return nullptr;
}

// ----------------
// Part class block
// ----------------

// Part constructors\destructors

Part::Part(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame) :
	Entity(title, description)
{
	this->linkSystem = linkSystem;
	this->shape = shape;
	frame = this->defaultFrame = defaultFrame;
	x = xRev = y = 0.0;
}

// Part getters

LinkSystem* Part::getLinkSystem()
{
	return linkSystem;
}

double Part::getX()
{
	return x;
}
double Part::getY()
{
	return y;
}

Shape* Part::getShape()
{
	return shape;
}

// Part setters

void Part::setLinkSystem(LinkSystem* linkSystem)
{
	this->linkSystem = linkSystem;
}

void Part::setX(double x)
{
	this->x = x;
}
void Part::setY(double y)
{
	this->y = y;
}

// Part methods

void Part::connect(int portIndex, Part* connection)
{
	linkSystem->addConnection(portIndex, connection, this);
}
void Part::show(int activePhase, bool reverse)
{
	shape->draw(x, y, activePhase, reverse);
}

bool Part::diffusion(Part* part)
{
	return shape->diffusion(part->shape, part->x - x, part->y - y);
}


// ----------------------
// LinkSystem class block
// ----------------------

// LinkSystem constructors\destructors

LinkSystem::LinkSystem(const char** title, const char** description, int linkCount, Link** connectors) :
	Entity(title, description)
{
	this->linkCount = linkCount;
	this->connectors = connectors;
	callbackIndex = 0;
}

// LinkSystem getters

int LinkSystem::getLinkCount()
{
	return linkCount;
}
Link** LinkSystem::getConnectors()
{
	return connectors;
}

// LinkSystem setters

void LinkSystem::setLinkCount(int linkCount)
{
	this->linkCount = linkCount;
}
void LinkSystem::setConnectors(Link** connectors)
{
	this->connectors = connectors;
}

// LinkSystem methods

void LinkSystem::addConnection(int linkIndex, Part* connection, Part* callback)
{
	if (linkIndex > 0 and linkIndex < linkCount and
		connectors[linkIndex]->getIdentifier() == connection->getLinkSystem()->connectors[0]->getIdentifier())
	{
		if (connectors[linkIndex]->getConnection())
		{
			connectors[linkIndex]->getConnection()->getLinkSystem()->connectors[0]->setConnection(nullptr);
			connectors[linkIndex]->getConnection()->getLinkSystem()->callbackIndex = 0;
		}
		if (connection->getLinkSystem()->connectors[0]->getConnection())
		{
			connection->getLinkSystem()->connectors[0]->getConnection()->getLinkSystem()->connectors[connection->getLinkSystem()->callbackIndex]->setConnection(nullptr);
		}
		connectors[linkIndex]->setConnection(connection);
		connection->getLinkSystem()->connectors[0]->setConnection(callback);
		connection->getLinkSystem()->callbackIndex = 0;

		connection->setX(callback->getX() + connectors[linkIndex]->getHorizontalDisplacement());
		connection->setY(callback->getY() + connectors[linkIndex]->getVerticalDisplacement());
	}
}


// ----------------
// Link class block
// ----------------

// Link constructors\destructors

Link::Link(const char** title, const char** description, int identifier, int horizontalDisplacementPxl, int verticalDisplacementPxl, int windowWidth, int windowHeight) :
	Entity(title, description)
{
	this->identifier = identifier;

	connection = nullptr;
	
	this->horizontalDisplacementPxl = horizontalDisplacementPxl;
	this->verticalDisplacementPxl = verticalDisplacementPxl;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->horizontalDisplacementPxl = horizontalDisplacementPxl;
	this->verticalDisplacementPxl = verticalDisplacementPxl;

	horizontalDisplacement = (double)(horizontalDisplacementPxl) / windowWidth * 2;
	verticalDisplacement = (double)(verticalDisplacementPxl) / windowHeight * 2;

	horizontalDisplacementRev = horizontalDisplacement * -1;
}

// Link getters

int Link::getIdentifier()
{
	return identifier;
}
Part* Link::getConnection()
{
	return connection;
}

double Link::getHorizontalDisplacement()
{
	return horizontalDisplacement;
}
double Link::getHorizontalDisplacementRev()
{
	return horizontalDisplacementRev;
}
double Link::getVerticalDisplacement()
{
	return verticalDisplacement;
}

// Link setters

void Link::setIdentifier(int identifier)
{
	this->identifier = identifier;
}
void Link::setConnection(Part* connection)
{
	this->connection = connection;
}

void Link::setHorizontalDisplacement(double horizontalDisplacement)
{
	this->horizontalDisplacement = horizontalDisplacement;
}
void Link::setVerticalDisplacement(double verticalDisplacement)
{
	this->verticalDisplacement = verticalDisplacement;
}
