#pragma once

#include "PartMaster.h"

class AccessoryMaster :
    public PartMaster
{
    int maxAccessoryIndex;

    int* partIndexes;

public:
    AccessoryMaster(int windowWidth, int windowHeight);

    Accessory* generateAccessory(int accessoryIndex, Frame* defaultFrame);
};

