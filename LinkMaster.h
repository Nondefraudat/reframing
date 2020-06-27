#pragma once

#include "Pieces.h"

class LinkMaster
{
	int maxLinkIndex;

	const char** titlePres;
	const char** descriptionPres;

	int* identifiersPres;

	int windowWidth;
	int windowHeight;

public:
	LinkMaster(int windowWidth, int windowHeight);

	Link* generateLink(int linkIndex, int horizontalDisplacementPxl, int verticalDisplacementPxl);
};

