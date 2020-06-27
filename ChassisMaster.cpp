#include "ChassisMaster.h"

ChassisMaster::ChassisMaster(int windowWidth, int windowHeight) :
	PartMaster(windowWidth, windowHeight)
{
	maxChassisIndex = 1;

	horisontalBoostMultPres = new double[maxChassisIndex];
	verticalBoostMultPres = new double[maxChassisIndex];

	maxHorisontalSpeedMultPres = new double[maxChassisIndex];
	maxVerticalSpeedMultPres = new double[maxChassisIndex];

	horisontalBreakMultPres = new double[maxChassisIndex];
	verticalBreakMultPres = new double[maxChassisIndex];

	jumpPowerMultPres = new double[maxChassisIndex];

	partIndexes = new int[maxChassisIndex];

	horisontalBoostMultPres[0] = 0.01;
	verticalBoostMultPres[0] = 0.0;

	maxHorisontalSpeedMultPres[0] = 0.2;
	maxVerticalSpeedMultPres[0] = 0.0;

	horisontalBreakMultPres[0] = 0.0;
	verticalBreakMultPres[0] = 0.0;

	jumpPowerMultPres[0] = 0.4;

	partIndexes[0] = 2;

}

Chassis* ChassisMaster::generateChassis(int chassisIndex, Frame* defaultFrame)
{
	if (chassisIndex < maxChassisIndex)
	{
		return new Chassis(&titlePres[partIndexes[chassisIndex]], &descriptionsPres[partIndexes[chassisIndex]],
			totalResistancePres[partIndexes[chassisIndex]],
			linkSystemMaster->generateLinkSystem(linkSystemInexes[partIndexes[chassisIndex]]),
			shapeMaster->generateShape(shapeIndexes[partIndexes[chassisIndex]]), defaultFrame,
			horisontalBoostMultPres[chassisIndex], verticalBoostMultPres[chassisIndex],
			maxHorisontalSpeedMultPres[chassisIndex], maxVerticalSpeedMultPres[chassisIndex],
			horisontalBreakMultPres[chassisIndex], verticalBreakMultPres[chassisIndex],
			jumpPowerMultPres[chassisIndex]);
	}
	return nullptr;
}
