#include "ChassisMaster.h"

ChassisMaster::ChassisMaster(int windowWidth, int windowHeight) :
	PartMaster(windowWidth, windowHeight)
{
	maxChassisIndex = 1;

	horisontalSpeedMultPres = new double[maxChassisIndex];
	verticalSpeedMultPres = new double[maxChassisIndex];
	partIndexes = new int[maxChassisIndex];

	horisontalSpeedMultPres[0] = 0.6;
	verticalSpeedMultPres[0] = 0.2;
	partIndexes[0] = 2;

}

Chassis* ChassisMaster::generateChassis(int chassisIndex, Frame* defaultFrame)
{
	if (chassisIndex < maxChassisIndex)
	{
		return new Chassis(&titlePres[partIndexes[chassisIndex]], &descriptionsPres[partIndexes[chassisIndex]],
			linkSystemMaster->generateLinkSystem(linkSystemInexes[partIndexes[chassisIndex]]),
			shapeMaster->generateShape(shapeIndexes[partIndexes[chassisIndex]]), defaultFrame,
			horisontalSpeedMultPres[chassisIndex],
			verticalSpeedMultPres[chassisIndex]);
	}
	return nullptr;
}
