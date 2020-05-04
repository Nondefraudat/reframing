#include "Processor.h"
#include <iostream>

Processor::Processor(int width, int height, CreationBase* base) 
	: FunctionalObject(width, height)
{
	itemTag = IT_PROCESOR;
	this->base = base;
}

Processor::~Processor()
{

}

int Processor::action(int& itemTag, int& operation)
{
	if (itemTag != IT_PROCESOR)
	{
		return AR_UNKNOWNOPERATION;
	}

	std::cout << "processor\n";

	operation = OL_GET_NEXTOPERATION;
	itemTag = IT_MEMORY;

	return base->action(itemTag, operation);
}

void Processor::work()
{
	int itemTag = IT_PROCESOR;
	int operation;

	action(itemTag, operation);
}
