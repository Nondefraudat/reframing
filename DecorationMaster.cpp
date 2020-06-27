#include "DecorationMaster.h"

DecorationMaster::DecorationMaster(int windowWidth, int windowHeight) :
	PartMaster(windowWidth, windowHeight)
{
	maxDecorationIndex = 1;
	partIndexes = new int[maxDecorationIndex];

	partIndexes[0] = 3;
}

Decoration* DecorationMaster::generateDecoration(int decorationIndex, Frame* defaultFrame)
{
	if (decorationIndex < maxDecorationIndex)
	{
		return new Decoration(&titlePres[partIndexes[decorationIndex]], &descriptionsPres[partIndexes[decorationIndex]],
			totalResistancePres[partIndexes[decorationIndex]],
			linkSystemMaster->generateLinkSystem(linkSystemInexes[partIndexes[decorationIndex]]),
			shapeMaster->generateShape(shapeIndexes[partIndexes[decorationIndex]]), defaultFrame);
	}
	return nullptr;
}
