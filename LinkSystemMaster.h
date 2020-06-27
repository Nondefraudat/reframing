#pragma once

#include "Pieces.h"

#include "LinkMaster.h"

class LinkSystemMaster
{
	class LinkMaster* linkMaster;

	int maxLinkSystemIndex;

	const char** titlePres;
	const char** descriptionPres;

	int* linkCountPres; 
	int** connectorIndexes;

	int** horizontalDisplacementPxlPres;
	int** verticalDisplacementPxlPres;

	int windowWidth;
	int windowHeight;

public:
	LinkSystemMaster(int windowWidth, int windowHeight);

	LinkSystem* generateLinkSystem(int linkSystemIndex);
};

