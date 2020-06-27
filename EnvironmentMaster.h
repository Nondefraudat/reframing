#pragma once
#include "FrameMaster.h"

class EnvironmentMaster :
    public FrameMaster
{
    int maxEnvironmentIndex;

    int* frameIndexes;

public:
    EnvironmentMaster(int windowWidth, int windowHeight);

    Environment* generateEnvirenment(int environmentIndex);
};

