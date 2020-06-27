#include "CreationMaster.h"

CreationMaster::CreationMaster(int windowWidth, int windowHeight) :
    FrameMaster(windowWidth, windowHeight)
{
    maxCreationIndex = 1;

    defaultSpawnPointXPxlPres = new int[maxCreationIndex];
    defaultSpawnPointYPxlPres = new int[maxCreationIndex];
    frameIndexes = new int[maxCreationIndex];

    defaultSpawnPointXPxlPres[0] = 0;
    defaultSpawnPointYPxlPres[0] = 0;
    frameIndexes[0] = 1;
}

Creation* CreationMaster::generateCreation(int creationIndex)
{
    if (creationIndex < maxCreationIndex)
    {
        return new Creation(&titlePres[frameIndexes[creationIndex]], &descriptionPres[frameIndexes[creationIndex]], windowWidth, windowHeight,
            gravityMultPres[frameIndexes[creationIndex]], defaultSpawnPointXPxlPres[creationIndex], defaultSpawnPointYPxlPres[creationIndex]);
    }
    return nullptr;
}
