#include "CreationBase.h"
#include <iostream>

CreationBase::CreationBase(int x, int y, int width, int height) 
	: FunctionalObject(x, y, width, height)
{
	connectors = new list<Connector*>;
	itemTag = IT_BASE;
}

CreationBase::~CreationBase()
{

}

void CreationBase::setX(int x)
{
	FunctionalObject::setX(x);

	list<Connector*>::iterator it = connectors->begin();
	while (it != connectors->end())
	{
		Connector* link = (*it)->getLink();
		if (link)
		{
			int fullyXOffset = (*it)->getXOffset() - link->getXOffset();
			
			FunctionalObject* callback = link->getCallback();
			callback->setX(x + fullyXOffset);
		}
		it++;
	}
}

void CreationBase::setY(int y)
{
	FunctionalObject::setY(y);

	list<Connector*>::iterator it = connectors->begin();
	while (it != connectors->end())
	{
		Connector* link = (*it)->getLink();
		if (link)
		{
			int fullyYOffset = (*it)->getYOffset() - link->getYOffset();

			FunctionalObject* callback = link->getCallback();
			callback->setY(y + fullyYOffset);
		}
		it++;
	}
}

int CreationBase::action(int& itemTag, int& operation)
{
	std::cout << "base\n";
	if (itemTag == IT_MEMORY)
	{
		itemTag = IT_TRANSMITTER;
	}
	int actionResult = AR_UNKNOWNOPERATION;
	list<Connector*>::iterator it = connectors->begin();
	while (it != connectors->end() and actionResult != AR_SUCCESS)
	{
		std::cout << "-.";
		actionResult = (*it)->getLink()->getCallback()->action(itemTag, operation);
		if (actionResult == AR_RESENDCOMMAND)
		{
			actionResult = action(itemTag, operation);
		}
		it++;
	}
	std::cout << "\n";
	return actionResult;
}
