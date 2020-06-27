#include "EnvironmentMaster.h"

EnvironmentMaster::EnvironmentMaster(int windowWidth, int windowHeight) :
	FrameMaster(windowWidth, windowHeight)
{
	maxEnvironmentIndex = 1;

	frameIndexes = new int[maxEnvironmentIndex];

	frameIndexes[0] = 0;
}

Environment* EnvironmentMaster::generateEnvirenment(int environmentIndex)
{
	if (environmentIndex < maxEnvironmentIndex)
	{
		return new Environment(&titlePres[frameIndexes[environmentIndex]], &descriptionPres[frameIndexes[environmentIndex]], windowWidth, windowHeight,
			gravityMultPres[frameIndexes[environmentIndex]]);
	}
	return nullptr;
}
