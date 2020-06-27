#include "AccessoryMaster.h"

AccessoryMaster::AccessoryMaster(int windowWidth, int windowHeight) :
	PartMaster(windowWidth, windowHeight)
{
	maxAccessoryIndex = 1;

	partIndexes = new int[maxAccessoryIndex];

	partIndexes[0] = 1;
}

Accessory* AccessoryMaster::generateAccessory(int accessoryIndex, Frame* defaultFrame)
{
	if (accessoryIndex < maxAccessoryIndex)
	{
		return new Accessory(&titlePres[partIndexes[accessoryIndex]], &descriptionsPres[partIndexes[accessoryIndex]],
			totalResistancePres[partIndexes[accessoryIndex]],
			linkSystemMaster->generateLinkSystem(linkSystemInexes[partIndexes[accessoryIndex]]),
			shapeMaster->generateShape(shapeIndexes[partIndexes[accessoryIndex]]), defaultFrame);
	}
	return nullptr;
}
