#include "PartMaster.h"

// Constructors\destruvtors

PartMaster::PartMaster(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	linkSystemMaster = new LinkSystemMaster(windowWidth, windowHeight);
	shapeMaster = new ShapeMaster(windowWidth, windowHeight);

	maxPartIndex = 5;
	titlePres = new const char*[maxPartIndex];
	descriptionsPres = new const char* [maxPartIndex];
	linkSystemInexes = new int[maxPartIndex];
	shapeIndexes = new int[maxPartIndex];
	totalResistancePres = new double[maxPartIndex];

	// Base

	titlePres[0] = "Base";
	descriptionsPres[0] = "No information given";
	linkSystemInexes[0] = 0;
	shapeIndexes[0] = 0;
	totalResistancePres[0] = 3.0;

	// Accessory

	titlePres[1] = "Accessory";
	descriptionsPres[1] = "No information given";
	linkSystemInexes[1] = 1;
	shapeIndexes[1] = 1;
	totalResistancePres[1] = 3.0;

	// Chassis

	titlePres[2] = "Chassis";
	descriptionsPres[2] = "No information given";
	linkSystemInexes[2] = 2;
	shapeIndexes[2] = 2;
	totalResistancePres[2] = 4.3;

	// Decoration

	titlePres[3] = "Decoration";
	descriptionsPres[3] = "No information given";
	linkSystemInexes[3] = 3;
	shapeIndexes[3] = 3;
	totalResistancePres[3] = 1.0;

	// ContactWeapon

	titlePres[4] = "ContactWeapon";
	descriptionsPres[4] = "No information given";
	linkSystemInexes[4] = 4;
	shapeIndexes[4] = 4;
	totalResistancePres[4] = 4.3;
}

