#include "BaseMaster.h"

BaseMaster::BaseMaster(int windowWidth, int windowHeight) :
    PartMaster(windowWidth, windowHeight)
{
    maxBaseIndex = 1;

    defaultSpawnPointDisplacementXPxlPres = new int[maxPartIndex];
    defaultSpawnPointDisplacementYPxlPres = new int[maxPartIndex];
    partIndexes = new int[maxBaseIndex];

    defaultSpawnPointDisplacementXPxlPres[0] = 0;
    defaultSpawnPointDisplacementYPxlPres[0] = 0;
    partIndexes[0] = 0;

}

Base* BaseMaster::generateBase(int baseIndex, Frame* defaultFrame)
{
    if (baseIndex < maxBaseIndex)
    {
        return new Base(&titlePres[partIndexes[baseIndex]], &descriptionsPres[partIndexes[baseIndex]], 
            linkSystemMaster->generateLinkSystem(linkSystemInexes[partIndexes[baseIndex]]), 
            shapeMaster->generateShape(shapeIndexes[partIndexes[baseIndex]]), defaultFrame,
            defaultSpawnPointDisplacementXPxlPres[baseIndex],
            defaultSpawnPointDisplacementYPxlPres[baseIndex],
            windowWidth, windowHeight);
    }
    return nullptr;
}
