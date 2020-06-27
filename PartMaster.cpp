#include "PartMaster.h"

// Constructors\destruvtors

PartMaster::PartMaster(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	linkSystemMaster = new LinkSystemMaster(windowWidth, windowHeight);
	shapeMaster = new ShapeMaster(windowWidth, windowHeight);

	maxPartIndex = 3;
	titlePres = new const char*[maxPartIndex];
	descriptionsPres = new const char* [maxPartIndex];
	linkSystemInexes = new int[maxPartIndex];
	shapeIndexes = new int[maxPartIndex];

	// Base

	titlePres[0] = "Base";
	descriptionsPres[0] = "No information given";
	linkSystemInexes[0] = 0;
	shapeIndexes[0] = 0;

	// Accessory

	titlePres[1] = "Accessory";
	descriptionsPres[1] = "No information given";
	linkSystemInexes[1] = 1;
	shapeIndexes[1] = 1;

	// Chassis

	titlePres[2] = "Chassis";
	descriptionsPres[2] = "No information given";
	linkSystemInexes[2] = 2;
	shapeIndexes[2] = 2;
}

