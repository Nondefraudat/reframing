#pragma once

#include "FunctionalObject.h"

class CreationBase :
	public FunctionalObject
{


public:
	CreationBase(int x, int y, int width, int height);
	~CreationBase();

	void setX(int x);
	void setY(int y);

	int action(int& itemTag, int& operation);
};

