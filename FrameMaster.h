#pragma once

#include "Pieces.h"
#include "BaseMaster.h"
#include "AccessoryMaster.h"
#include "ChassisMaster.h"


class FrameMaster
{
protected:
	PartMaster* partMaster;

	int maxFrameIndex;

	const char** titlePres; 
	const char** descriptionPres;

	int* identifierPres;

	double* gravityMultPres;

	int windowWidth;
	int windowHeight;

public:
	FrameMaster(int windowWidth, int windowHeight);
};

