#include "LinkMaster.h"

// Constructors\destructors

LinkMaster::LinkMaster(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	maxLinkIndex = 3;

	titlePres = new const char* [maxLinkIndex];
	descriptionPres = new const char* [maxLinkIndex];
	identifiersPres = new int[maxLinkIndex];

	// Base test link

	titlePres[0] = "Base link";
	descriptionPres[0] = "No information given";
	identifiersPres[0] = 0;

	// Accessory test link

	titlePres[1] = "Accessory link";
	descriptionPres[1] = "No information given";
	identifiersPres[1] = 1;

	// Chassis test link

	titlePres[2] = "Chassis test link";
	descriptionPres[2] = "No information given";
	identifiersPres[2] = 2;
}

// Methods

Link* LinkMaster::generateLink(int linkIndex, int horizontalDisplacementPxl, int verticalDisplacementPxl)
{
	if (linkIndex < maxLinkIndex)
	{
		return new Link(&titlePres[linkIndex], &descriptionPres[linkIndex], identifiersPres[linkIndex], horizontalDisplacementPxl, verticalDisplacementPxl, windowWidth, windowHeight);
	}
	return nullptr;
}
