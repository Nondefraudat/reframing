#include "LinkSystemMaster.h"

// Constructors\destructors

LinkSystemMaster::LinkSystemMaster(int windowWidth, int windowHeight)
{
	linkMaster = new LinkMaster(windowWidth, windowHeight);

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	maxLinkSystemIndex = 5;

	titlePres = new const char* [maxLinkSystemIndex];
	descriptionPres = new const char* [maxLinkSystemIndex];
	linkCountPres = new int[maxLinkSystemIndex];
	connectorIndexes = new int* [maxLinkSystemIndex];
	horizontalDisplacementPxlPres = new int*[maxLinkSystemIndex];
	verticalDisplacementPxlPres = new int* [maxLinkSystemIndex];

	// Base

	titlePres[0] = "Base link system";
	descriptionPres[0] = "No onformation given";
	linkCountPres[0] = 4;
	connectorIndexes[0] = new int[linkCountPres[0]];
	{
		connectorIndexes[0][0] = 0;
		connectorIndexes[0][1] = 1;
		connectorIndexes[0][2] = 2;
		connectorIndexes[0][3] = 3;
	}
	horizontalDisplacementPxlPres[0] = new int[linkCountPres[0]];
	verticalDisplacementPxlPres[0] = new int[linkCountPres[0]];
	{
		horizontalDisplacementPxlPres[0][0] = 0;
		verticalDisplacementPxlPres[0][0] = 0;

		horizontalDisplacementPxlPres[0][1] = 0;
		verticalDisplacementPxlPres[0][1] = 0;

		horizontalDisplacementPxlPres[0][2] = 0;
		verticalDisplacementPxlPres[0][2] = 0;

		horizontalDisplacementPxlPres[0][3] = 0;
		verticalDisplacementPxlPres[0][3] = 0;
	}

	// Accessory

	titlePres[1] = "Accessory link system";
	descriptionPres[1] = "No onformation given";
	linkCountPres[1] = 1;
	connectorIndexes[1] = new int[linkCountPres[1]];
	{
		connectorIndexes[1][0] = 1;
	}
	horizontalDisplacementPxlPres[1] = new int[linkCountPres[1]];
	verticalDisplacementPxlPres[1] = new int[linkCountPres[1]];
	{
		horizontalDisplacementPxlPres[1][0] = 0;
		verticalDisplacementPxlPres[1][0] = 0;
	}

	// Chassis

	titlePres[2] = "Chassis link system";
	descriptionPres[2] = "No onformation given";
	linkCountPres[2] = 1;
	connectorIndexes[2] = new int[linkCountPres[2]];
	{
		connectorIndexes[2][0] = 2;
	}
	horizontalDisplacementPxlPres[2] = new int[linkCountPres[2]];
	verticalDisplacementPxlPres[2] = new int[linkCountPres[2]];
	{
		horizontalDisplacementPxlPres[2][0] = 0;
		verticalDisplacementPxlPres[2][0] = 0;
	}

	// Decoration

	titlePres[3] = "Chassis link system";
	descriptionPres[3] = "No onformation given";
	linkCountPres[3] = 0;
	connectorIndexes[3] = new int[linkCountPres[3]];
	horizontalDisplacementPxlPres[3] = new int[linkCountPres[3]];
	verticalDisplacementPxlPres[3] = new int[linkCountPres[3]];

	// ContactWeapon

	titlePres[4] = "Contact weapon link system";
	descriptionPres[4] = "No onformation given";
	linkCountPres[4] = 1;
	connectorIndexes[4] = new int[linkCountPres[4]];
	{
		connectorIndexes[4][0] = 3;
	}
	horizontalDisplacementPxlPres[4] = new int[linkCountPres[4]];
	verticalDisplacementPxlPres[4] = new int[linkCountPres[4]];
	{
		horizontalDisplacementPxlPres[4][0] = 0;
		verticalDisplacementPxlPres[4][0] = 0;
	}
}

// Methods

LinkSystem* LinkSystemMaster::generateLinkSystem(int linkSystemIndex)
{
	if (linkSystemIndex < maxLinkSystemIndex)
	{
		Link** connectors = new Link * [linkCountPres[linkSystemIndex]];
		for (int i = 0; i < linkCountPres[linkSystemIndex]; i++)
		{
			connectors[i] = linkMaster->generateLink(connectorIndexes[linkSystemIndex][i], horizontalDisplacementPxlPres[linkSystemIndex][i], verticalDisplacementPxlPres[linkSystemIndex][i]);
		}
		return new LinkSystem(&titlePres[linkSystemIndex], &descriptionPres[linkSystemIndex], linkCountPres[linkSystemIndex], connectors);
	}
	return nullptr;
}
