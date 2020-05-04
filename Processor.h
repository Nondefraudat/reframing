#pragma once

#include "FunctionalObject.h"
#include "CreationBase.h"

class Processor :
	public FunctionalObject
{
	CreationBase* base;

public:
	Processor(int width, int height, CreationBase* base);
	~Processor();

	int action(int& itemTag, int& operation);
	
	void work();
};
