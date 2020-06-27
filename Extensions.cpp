#include "Extensions.h"


// ----------------
// Creation class block
// ----------------

// Creaation constructors\destructors

Creation::Creation(const char** title, const char** description, int windowWidth, int windowHeight, double gravityMult, int defaultSpawnPointXPxl, int defaultSpawnPointYPxl) :
	Frame(title, description, windowWidth, windowHeight, gravityMult)
{
	defaultSpawnPointX = (double)defaultSpawnPointXPxl / windowWidth * 2;
	defaultSpawnPointY = (double)defaultSpawnPointYPxl / windowHeight * 2;

	firstBase = lastBase = new Node<Base>(nullptr);
	firstChassis = lastChassis = new Node<Chassis>(nullptr);
}

// Creeation methods

void Creation::addBase(Base* base)
{
	lastBase->next = new Node<Base>(base);
	lastBase->next->prev = lastBase;
	lastBase = lastBase->next;
}

void Creation::addChassis(Chassis* chassis)
{
	lastChassis->next = new Node<Chassis>(chassis);
	lastChassis->next->prev = lastChassis;
	lastChassis = lastChassis->next;
}

void Creation::removeBase(Base* base)
{
	Node<Base>* currentNode = firstBase;
	while (currentNode->next and currentNode->value != base)
	{
		currentNode = currentNode->next;
	}
	if (currentNode->value == base)
	{
		currentNode->prev->next = currentNode->next;
		if (currentNode->next)
		{
			currentNode->next->prev = currentNode->prev;
		}
		delete(currentNode);
	}
}

void Creation::removeChassis(Chassis* chassis)
{
	Node<Chassis>* currentNode = firstChassis;
	while (currentNode->next and currentNode->value != chassis)
	{
		currentNode = currentNode->next;
	}
	if (currentNode->value == chassis)
	{
		currentNode->prev->next = currentNode->next;
		if (currentNode->next)
		{
			currentNode->next->prev = currentNode->prev;
		}
		delete(currentNode);
	}
}

void Creation::spawnInXY(double x, double y)
{
	double factorX = x, factorY = y;
	Node<Base>* currentBase = firstBase;
	if (currentBase->next)
	{
		currentBase = currentBase->next;
		factorX -= currentBase->value->getX();
		factorY -= currentBase->value->getY();
	}
	Node<Part>* currentPart = firstPart;
	while (currentPart->next)
	{
		currentPart = currentPart->next;
		currentPart->value->setX(currentPart->value->getX() + factorX);
		currentPart->value->setY(currentPart->value->getY() + factorY);
	}
}

void Creation::moveToXY(double x, double y, Node<Frame>* firstFrame)
{
	Node<Base>* currentBase = firstBase;
	while (currentBase->next)
	{
		currentBase = currentBase->next;

		double horisontalMult = 0.0;
		double verticalMult = 0.0;
		
		Node<Chassis>* currentChassis = firstChassis;
		while (currentChassis->next)
		{
			currentChassis = currentChassis->next;
			if (currentChassis->value->getLinkSystem()->getConnectors()[0]->getConnection() == currentBase->value)
			{
				horisontalMult = (horisontalMult + currentChassis->value->getHorizontalSpeedMult()) / 2;
				verticalMult = (verticalMult + currentChassis->value->getVerticalSpeedMult()) / 2;
			}
		}
		
		double differenceX = x - currentBase->value->getX();
		double differenceY = y - currentBase->value->getY();
		
		double range = sqrt(pow(differenceX, 2) + pow(differenceY, 2));

		double horisontalFactor = ((double)10 * horisontalMult) / windowWidth * 2;
		double verticalFactor = ((double)10 * verticalMult) / windowHeight * 2;

		double factorX;
		double factorY;
		if (range)
		{
			factorX = currentBase->value->getX() + differenceX * (horisontalFactor / range);
			factorY = currentBase->value->getY() + differenceY * (verticalFactor / range);
		}
		else
		{
			factorX = currentBase->value->getX();
			factorY = currentBase->value->getY();
		}

		double prevX = currentBase->value->getX();
		double prevY = currentBase->value->getY();

		if (factorX < prevX)
		{
			reverse = true;
		}
		else
		{
			if (factorX > prevX)
			{
				reverse = false;
			}
		}
		phase = 1;
		if (range <= sqrt(pow(factorX - prevX, 2) + pow(factorY - prevY, 2)))
		{
			factorX = x;
			factorY = y;
			phase = 0;
		}
		Part* part = nullptr;
		spawnInXY(factorX, factorY);
		part = diffusion(firstFrame);
		if (part)
		{
			differenceX = part->getX() - factorX;
			differenceY = part->getY() - factorY;

			differenceX /= abs(differenceX);
			differenceY /= abs(differenceY);

			horisontalFactor = (double)1 / windowWidth * 2 * differenceX;
			verticalFactor = (double)1 / windowHeight * 2 * differenceY;

			factorX -= horisontalFactor;
			factorY -= verticalFactor;
			spawnInXY(factorX, factorY);
		}
	}
}

void Creation::moveToRight(Node<Frame>* firstFrame)
{
	Node<Base>* currentBase = firstBase;
	while (currentBase->next)
	{
		currentBase = currentBase->next;

		double horisontalMult = 0.0;

		Node<Chassis>* currentChassis = firstChassis;
		while (currentChassis->next)
		{
			currentChassis = currentChassis->next;
			if (currentChassis->value->getLinkSystem()->getConnectors()[0]->getConnection() == currentBase->value)
			{
				horisontalMult = (horisontalMult + currentChassis->value->getHorizontalSpeedMult()) / 2;
			}
		}

		double prevX = currentBase->value->getX();
		double prevY = currentBase->value->getY();

		double factorX = prevX + horisontalMult;
		double factorY = prevY;

		Part* part = nullptr;
		do
		{
			spawnInXY(factorX, factorY);
			part = diffusion(firstFrame);
			if (part)
			{
				double differenceX = part->getX() - factorX;
				double differenceY = part->getX() - factorX;

				if (differenceX != 0)
				{
					differenceX /= abs(differenceX);
				}
				if (differenceY != 0)
				{
					differenceY /= abs(differenceY);
				}

				double horisontalFactor = (double)1 / windowWidth * 2 * differenceX;
				double verticalFactor = (double)1 / windowHeight * 2 * differenceY;

				factorX += horisontalFactor;
				factorY += verticalFactor;
			}
		} while (part);
	}
}

void Creation::moveToLeft(Node<Frame>* firstFrame)
{
	Node<Base>* currentBase = firstBase;
	while (currentBase->next)
	{
		currentBase = currentBase->next;

		double horisontalMult = 0.0;

		Node<Chassis>* currentChassis = firstChassis;
		while (currentChassis->next)
		{
			currentChassis = currentChassis->next;
			if (currentChassis->value->getLinkSystem()->getConnectors()[0]->getConnection() == currentBase->value)
			{
				horisontalMult = (horisontalMult + currentChassis->value->getHorizontalSpeedMult()) / 2;
			}
		}

		double prevX = currentBase->value->getX();
		double prevY = currentBase->value->getY();

		double factorX = prevX - horisontalMult;
		double factorY = prevY;

		Part* part = nullptr;
		do
		{
			spawnInXY(factorX, factorY);
			part = diffusion(firstFrame);
			if (part)
			{
				double differenceX = part->getX() - factorX;
				double differenceY = part->getX() - factorX;

				if (differenceX != 0)
				{
					differenceX /= abs(differenceX);
				}
				if (differenceY != 0)
				{
					differenceY /= abs(differenceY);
				}

				double horisontalFactor = (double)1 / windowWidth * 2 * differenceX;
				double verticalFactor = (double)1 / windowHeight * 2 * differenceY;

				factorX += horisontalFactor;
				factorY += verticalFactor;
			}
		} while (part);
	}
}

void Creation::moveToUp(Node<Frame>* firstFrame)
{
}

void Creation::moveToDown(Node<Frame>* firstFrame)
{
}

void Creation::jump()
{

}


// -----------------------
// Environment class block
// -----------------------

// Envirenment constructors\destructors

Environment::Environment(const char** title, const char** description, int windowWidth, int windowHeight, double gravityMult) :
	Frame(title, description, windowWidth, windowHeight, gravityMult)
{

}

// Environment methods

void Environment::moveToXY(double x, double y, Node<Frame>* firstFrame)
{
	spawnInXY(x, y);
}

void Environment::spawnInXY(double x, double y)
{
	Node<Part>* currentPart = firstPart;
	if (currentPart->next)
	{
		double differenceX = x - currentPart->next->value->getX();
		double differenceY = y - currentPart->next->value->getY();
		while (currentPart->next)
		{
			currentPart = currentPart->next;
			currentPart->value->setX(currentPart->value->getX() + x);
			currentPart->value->setY(currentPart->value->getY() + y);
		}
	}
}


// ----------------
// Base class block
// ----------------

// Base constructions\destructions

Base::Base(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame, int defaultSpawnPointDisplacementPxlX, int defaultSpawnPointDisplacementPxlY, int windowWidth, int windowHeight) :
	Part(title, description, linkSystem, shape, defaultFrame)
{
	defaultSpawnPointDisplacementX = (double)defaultSpawnPointDisplacementPxlX / windowWidth * 2;
	defaultSpawnPointDisplacementY = (double)defaultSpawnPointDisplacementPxlY / windowHeight * 2;
}


// -------------------
// Chassis class block
// -------------------

// Chassis constructors\destrructors

Chassis::Chassis(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame, double horisontalSpeedMult, double verticalSpeedMult) :
	Part(title, description, linkSystem, shape, defaultFrame)
{
	this->horisontalSpeedMult = horisontalSpeedMult;
	this->verticalSpeedMult = verticalSpeedMult;
}

// Chassis getters

double Chassis::getHorizontalSpeedMult()
{
	return horisontalSpeedMult;
}

double Chassis::getVerticalSpeedMult()
{
	return verticalSpeedMult;
}

// ---------------------
// Accessory class block
// ---------------------

// Accessory constructors\destructors

Accessory::Accessory(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame) :
	Part(title, description, linkSystem, shape, defaultFrame)
{

}

// Accessory methods

bool Accessory::diffusion(Part* part)
{
	return false;
}
