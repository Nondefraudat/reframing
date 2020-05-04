#include "Transmitter.h"

#include <iostream>

Transmitter::Transmitter(int width, int height)
	: FunctionalObject(width, height)
{
	itemTag = IT_TRANSMITTER;
	operation = OL_PASS;
}

Transmitter::~Transmitter()
{
	
}

int Transmitter::action(int& itemTag, int& operation)
{
	if (itemTag != IT_TRANSMITTER)
	{
		return AR_UNKNOWNOPERATION;
	}
	cout << "transmitter\n";

	itemTag = IT_CHASSIS;
	operation = this->operation;
	this->operation = OL_PASS;
	
	return AR_RESENDCOMMAND;
}

void Transmitter::setOperation(int operation)
{
	std::cout << "okk\n";
	this->operation = operation;
}
