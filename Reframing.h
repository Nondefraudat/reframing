#pragma once

#include <list>
#include <iostream>

#include "SDL/SDL.h"
#include "GL/glew.h"

#include "Node.h"
#include "CreationMaster.h"
#include "EnvironmentMaster.h"
#include "ContactWeaponMaster.h"


enum AppStatuses
{
	AS_ON = 1,
	AS_OFF = 0
};

using namespace std;

class Reframing
{
	CreationMaster* creationMaster;
	EnvironmentMaster* environmentMaster;

	SDL_Window* window;
	int windowWidth;
	int windowHeight;
	int appStatus;

	Frame* userFrame;

	Node<Frame>* firstFrame, * lastFrame;
	Environment* envirenment;

public:
	Reframing();
	~Reframing();

	void run();

private:
	void initSystems();
	void initShaders();
	void eventLoop();
	void inputProcess();
	void redrawEverything();
};
