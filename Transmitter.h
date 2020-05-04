#pragma once

#include "FunctionalObject.h"

class Transmitter :
	public FunctionalObject
{
private:
	int operation;

public:
	Transmitter(int width, int height);
	~Transmitter();

	int action(int& itemTag, int& operation);

	void setOperation(int operation);
};

