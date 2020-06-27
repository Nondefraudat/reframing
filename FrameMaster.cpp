#include "FrameMaster.h"

// Constructors\destructors

FrameMaster::FrameMaster(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth; 
	this->windowHeight = windowHeight;

	partMaster = new PartMaster(windowWidth, windowHeight);

	maxFrameIndex = 2;

	titlePres = new const char* [maxFrameIndex];
	descriptionPres = new const char* [maxFrameIndex];
	identifierPres = new int[maxFrameIndex];
	gravityMultPres = new double[maxFrameIndex];

	titlePres[0] = "Envirenment";
	descriptionPres[0] = "No information given";
	identifierPres[0] = 0;
	gravityMultPres[0] = 0.0;

	titlePres[0] = "Test frame";
	descriptionPres[0] = "No information given";
	identifierPres[0] = 1;
	gravityMultPres[0] = 1.0;
}
