#pragma once

#include "PartMaster.h"

class DecorationMaster :
    public PartMaster
{
    int maxDecorationIndex;

    int* partIndexes;

public:
    DecorationMaster(int windowWidth, int windowHeight);

    Decoration* generateDecoration(int decorationIndex, Frame* defaultFrame);
};

