#pragma once

#include "LinkSystemMaster.h"
#include "ShapeMaster.h"

#include "Extensions.h"

class PartMaster
{
protected:

	LinkSystemMaster* linkSystemMaster;
	ShapeMaster* shapeMaster;
	
	int maxPartIndex;
	 
	const char** titlePres;
	const char** descriptionsPres;

	int* linkSystemInexes;
	int* shapeIndexes;
	
	double* totalResistancePres;

	int windowWidth;
	int windowHeight;

public:
	PartMaster(int windowWidth, int windowHeight);
};

