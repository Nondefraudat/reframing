#pragma once

#include "FrameMaster.h"

class CreationMaster :
    public FrameMaster
{
	int maxCreationIndex;

	int* defaultSpawnPointXPxlPres;
	int* defaultSpawnPointYPxlPres;

	int* frameIndexes;

public:
	CreationMaster(int windowWidth, int windowHeight);

	Creation* generateCreation(int creationIndex);
};

