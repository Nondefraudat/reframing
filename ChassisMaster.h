#pragma once

#include "PartMaster.h"

class ChassisMaster :
    public PartMaster
{
    int maxChassisIndex;

    double* horisontalSpeedMultPres;
    double* verticalSpeedMultPres;

    int* partIndexes;

public:
    ChassisMaster(int windowWidth, int windowHeight);

    Chassis* generateChassis(int chassisIndex, Frame* defaultFrame);
};

