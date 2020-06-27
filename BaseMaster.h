#pragma once

#include "PartMaster.h"

class BaseMaster :
    public PartMaster
{
	int maxBaseIndex;

	int* defaultSpawnPointDisplacementXPxlPres;
	int* defaultSpawnPointDisplacementYPxlPres;

	int* partIndexes;

public:
	BaseMaster(int windowWidth, int windowHeight);

	Base* generateBase(int baseIndex, Frame* defaultFrame);
};

