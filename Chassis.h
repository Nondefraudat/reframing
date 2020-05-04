#pragma once

#include "FunctionalObject.h"
#include "CreationBase.h"

class Chassis :
	public FunctionalObject
{
	CreationBase* base;
public:
	Chassis(int width, int height, CreationBase* base);
	~Chassis();

	int action(int& itemTag, int& operation);
};


