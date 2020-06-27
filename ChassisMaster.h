#pragma once

#include "PartMaster.h"

class ChassisMaster :
    public PartMaster
{
    int maxChassisIndex;
	
	double* horisontalBoostMultPres;
	double* verticalBoostMultPres;

	double* maxHorisontalSpeedMultPres;
	double* maxVerticalSpeedMultPres;

	double* horisontalBreakMultPres;
	double* verticalBreakMultPres;

	double* jumpPowerMultPres;

    int* partIndexes;

public:
    ChassisMaster(int windowWidth, int windowHeight);

    Chassis* generateChassis(int chassisIndex, Frame* defaultFrame);
};

