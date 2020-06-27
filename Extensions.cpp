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

	horisontalSpeed = 0.0;
	verticalSpeed = 0.0;

	horisontalBoost = 0.0;
	verticalBoost = 0.0;

	maxHorisontalSpeed = 0.0;
	maxVerticalSpeed = 0.0;

	defaultHorisontalFactor = (double)10 / windowWidth * 2;
	defaultVerticalFactor = (double)10 / windowHeight * 2;

	gravitationFactor = gravityMult * defaultVerticalFactor;
	fallRate = 0.0;

	jumpPower = 0.0;
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

	double addHorisontalBoost = lastChassis->value->getHorizontalBoostMult() * defaultHorisontalFactor;
	double addVerticalBoost = lastChassis->value->getVerticalBoostMult() * defaultVerticalFactor;

	double addMaxHorisontalSpeed = lastChassis->value->getMaxHorisontalSpeedMult() * defaultHorisontalFactor;
	double addMaxVerticalSpeed = lastChassis->value->getMaxVerticalSpeedMult() * defaultVerticalFactor;

	horisontalBoost += addHorisontalBoost;
	verticalBoost += addVerticalBoost;

	if (maxHorisontalSpeed == 0.0)
	{
		maxHorisontalSpeed = addMaxHorisontalSpeed;
	}
	else
	{
		if (maxHorisontalSpeed > addMaxHorisontalSpeed)
		{
			maxHorisontalSpeed = addMaxHorisontalSpeed;
		}
	}
	if (maxVerticalSpeed == 0.0)
	{
		maxVerticalSpeed = addMaxVerticalSpeed;
	}
	else
	{
		if (maxVerticalSpeed > addMaxVerticalSpeed)
		{
			maxVerticalSpeed = addMaxVerticalSpeed;
		}
	}

	double addJumpPower = lastChassis->value->getJumpPowerMult() * defaultVerticalFactor;

	jumpPower += addJumpPower;
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
	if (firstBase->next)
	{
		double sourceX = firstBase->next->value->getX();
		double sourceY = firstBase->next->value->getY();

		double diffrenceX = x - sourceX;
		double diffrenceY = y - sourceY;

		gravitation(firstFrame);
		horisontalMove(diffrenceX, firstFrame);
		verticalMove(diffrenceY, firstFrame);
		for (int i = 0; i < 8; i++)
		{
			tryToGetOut(firstFrame);
		}
	}
}

void Creation::horisontalMove(double distance, Node<Frame>* firstFrame)
{
	if (firstBase->next)
	{
		double factor = 0.0;
		if (distance != 0.0)
		{
			factor = distance / abs(distance);
		}

		horisontalSpeed += horisontalBoost * factor;
		if (abs(horisontalSpeed) > maxHorisontalSpeed)
		{
			horisontalSpeed = maxHorisontalSpeed * factor;
		}

		phase = 1;
		if (factor == 0.0)
		{
			phase = 0;
			horisontalSpeed = 0.0;
		}
		else
		{
			if (factor < 0.0)
			{
				reverse = true;
				if (horisontalSpeed < distance)
				{
					horisontalSpeed = distance;
					phase = 0;
				}
			}
			else
			{
				reverse = false;
				if (horisontalSpeed > distance)
				{
					horisontalSpeed = distance;
					phase = 0;
				}
			}
		}

		double sourceX = firstBase->next->value->getX();
		double sourceY = firstBase->next->value->getY();

		double factorX = (double)1 / windowWidth * 2;
		double addX = 0.0;
		double absHorisontalSpeed = abs(horisontalSpeed);
		Part* part = diffusion(firstFrame);

		if (!part)
		{
			while (!part and addX < absHorisontalSpeed)
			{
				addX += factorX;
				if (addX > absHorisontalSpeed)
				{
					addX = absHorisontalSpeed;
				}
				spawnInXY(sourceX + addX * factor, sourceY);
				part = diffusion(firstFrame);
			}
			if (part)
			{
				horisontalSpeed = 0.0;
				if (fallRate < 0.0)
				{
					fallRate = abs(gravitationFactor);
				}
				addX -= factorX;
				spawnInXY(sourceX + addX * factor, sourceY);
				part = diffusion(firstFrame);
			}
		}
	}
}

void Creation::verticalMove(double distance, Node<Frame>* firstFrame)
{
	if (firstBase->next and distance != 0.0)
	{
		double factor = 0.0;
		if (distance != 0.0)
		{
			factor = distance / abs(distance);
		}

		verticalSpeed += verticalBoost * factor;
		if (abs(verticalSpeed) > maxVerticalSpeed)
		{
			verticalSpeed = maxVerticalSpeed * factor;
		}

		if (factor == 0.0)
		{
			verticalSpeed = 0.0;
		}
		else
		{
			if (factor < 0.0)
			{
				if (verticalSpeed < distance)
				{
					verticalSpeed = distance;
				}
			}
			else
			{
				if (verticalSpeed > distance)
				{
					verticalSpeed = distance;
				}
			}
		}

		double sourceX = firstBase->next->value->getX();
		double sourceY = firstBase->next->value->getY();

		double factorY = (double)1 / windowHeight * 2;
		double addY = 0.0;
		double absVerticalSpeed = abs(verticalSpeed);
		Part* part = diffusion(firstFrame);

		if (!part)
		{
			while (!part and addY < absVerticalSpeed)
			{
				addY += factorY;
				if (addY > absVerticalSpeed)
				{
					addY = absVerticalSpeed;
				}
				spawnInXY(sourceX, sourceY + addY * factor);
				part = diffusion(firstFrame);
			}
			if (part)
			{
				verticalSpeed = 0.0; 
				if (fallRate < 0.0)
				{
					fallRate = abs(gravitationFactor);
				}
				addY -= factorY;
				spawnInXY(sourceX, sourceY + addY * factor);
				part = diffusion(firstFrame);
			}
		}
	}
}

void Creation::gravitation(Node<Frame>* firstFrame)
{
	if (firstBase->next)
	{	
		fallRate += gravitationFactor;
		
		double factor = 0.0;
		if (fallRate != 0.0)
		{
			factor = fallRate / abs(fallRate);
		}
		

		double sourceX = firstBase->next->value->getX();
		double sourceY = firstBase->next->value->getY();

		double factorY = (double)1 / windowHeight * 2;
		double addY = 0.0;
		double absFallRate = abs(fallRate);
		Part* part = diffusion(firstFrame);

		if (!part)
		{
			while (!part and addY < absFallRate)
			{
				addY += factorY;
				spawnInXY(sourceX, sourceY - addY * factor);
				part = diffusion(firstFrame);
			}
			if (part)
			{
				if (fallRate < 0.0)
				{
					fallRate = abs(gravitationFactor);
				}
				else
				{
					fallRate = 0.0;
				}
				addY -= factorY;
				spawnInXY(sourceX, sourceY - addY * factor);
				part = diffusion(firstFrame);
			}
		}
		
	}
}

void Creation::tryToGetOut(Node<Frame>* firstFrame)
{
	if (firstBase->next)
	{
		Part* part = diffusion(firstFrame);
		
		if (part)
		{
			if (fallRate < 0.0)
			{
				fallRate = abs(gravitationFactor);
			}
			double sourceX = firstBase->next->value->getX(); 
			double sourceY = firstBase->next->value->getY();

			double differenceX = sourceX - part->getX();
			double differenceY = sourceY - part->getY();

			int differenceXPxl = round(differenceX / 2 * windowWidth);
			int differenceYPxl = round(differenceY / 2 * windowHeight);

			Shape* shape_1 = firstBase->next->value->getShape();
			Shape* shape_2 = part->getShape();

			double horisontalFactor = 1;
			double verticalFactor = 1;

			double ratioX = 0.0;
			if (differenceX != 0.0)
			{
				if (differenceX < 0.0)
				{
					ratioX = (differenceX + shape_1->getMaxX()) / (shape_2->getMinX());
					horisontalFactor *= -1;
				}
				else
				{
					ratioX = (differenceX + shape_1->getMinX()) / (shape_2->getMaxX());
				}
			}

			double ratioY = 0.0;
			if (differenceY != 0.0)
			{
				if (differenceY < 0.0)
				{
					ratioY = (differenceY + shape_1->getMaxY()) / (shape_2->getMinY());
					verticalFactor *= -1;
				}
				else
				{
					ratioY = (differenceY + shape_1->getMinY()) / (shape_2->getMaxY());
				}
			}

			if (ratioY > ratioX)
			{
				double factorY = (double)1 / windowHeight * 2 * verticalFactor;
				sourceY += factorY;
			}
			else
			{
				double factorX = (double)1 / windowWidth * 2 * horisontalFactor;
				sourceX += factorX;
			}
			spawnInXY(sourceX, sourceY);
		}
	}
}

void Creation::jump(Node<Frame>* firstFrame)
{
	if (fallRate == 0.0)
	{
		fallRate = -jumpPower;
	}
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

Base::Base(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame, int defaultSpawnPointDisplacementPxlX, int defaultSpawnPointDisplacementPxlY, int windowWidth, int windowHeight) :
	Part(title, description, totalResistance, linkSystem, shape, defaultFrame)
{
	defaultSpawnPointDisplacementX = (double)defaultSpawnPointDisplacementPxlX / windowWidth * 2;
	defaultSpawnPointDisplacementY = (double)defaultSpawnPointDisplacementPxlY / windowHeight * 2;
}


// -------------------
// Chassis class block
// -------------------

// Chassis constructors\destrructors

Chassis::Chassis(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame,
	double horisontalBoostMult, double verticalBoostMult,
	double maxHorisontalSpeedMult, double maxVerticalSpeedMult,
	double horisontalBreakMult, double verticalBreakMult, 
	double jumpPowerMult) :
	Part(title, description, totalResistance, linkSystem, shape, defaultFrame)
{
	this->horisontalBoostMult = horisontalBoostMult;
	this->verticalBoostMult = verticalBoostMult;
	this->maxHorisontalSpeedMult = maxHorisontalSpeedMult;
	this->maxVerticalSpeedMult = maxVerticalSpeedMult;
	this->horisontalBreakMult = horisontalBreakMult;
	this->verticalBreakMult = verticalBreakMult;
	this->jumpPowerMult = jumpPowerMult;
}

// Chassis getters

double Chassis::getHorizontalBoostMult()
{
	return horisontalBoostMult;
}

double Chassis::getVerticalBoostMult()
{
	return verticalBoostMult;
}

double Chassis::getMaxHorisontalSpeedMult()
{
	return maxHorisontalSpeedMult;
}

double Chassis::getMaxVerticalSpeedMult()
{
	return maxVerticalSpeedMult;
}

double Chassis::getHorisontalBreakMult()
{
	return horisontalBreakMult;
}

double Chassis::getVerticalBreakMult()
{
	return verticalBreakMult;
}

double Chassis::getJumpPowerMult()
{
	return jumpPowerMult;
}

// ---------------------
// Accessory class block
// ---------------------

// Accessory constructors\destructors

Accessory::Accessory(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame) :
	Part(title, description, totalResistance, linkSystem, shape, defaultFrame)
{
	shape->setPhisical(false);
}

// Accessory methods

bool Accessory::diffusion(Part* part)
{
	return false;
}

// ----------------------
// Decoration class block
// ----------------------

// Decoration constructors\desctructors

Decoration::Decoration(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame) :
	Part(title, description, totalResistance, linkSystem, shape, defaultFrame)
{

}

// -------------------------
// ContactWeapon class block
// -------------------------

// ContactWeapon constructors\destructors;

ContactWeapon::ContactWeapon(const char** title, const char** description, double totalResistance, double contactDamageMult, 
	LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame) :
	Part(title, description, totalResistance, linkSystem, shape, defaultFrame)
{
	this->contactDamageMult = contactDamageMult;
}

// ContactWeapon methods

void ContactWeapon::show(int activePhase, bool reverse)
{
	glColor3d(1.0, 0.0, 0.0);
	std::cout << "ok";
	Part::show(activePhase, reverse);
	glColor3b(1.0, 1.0, 1.0);
}
