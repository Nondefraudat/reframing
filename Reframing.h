#pragma once

#include <list>
#include <iostream>

#include "SDL/SDL.h"
#include "GL/glew.h"

#include "Creation.h"

enum AppStatuses
{
	AS_ON = 1,
	AS_OFF = 0
};

using namespace std;

class Processor;

class Reframing
{
	SDL_Window* window;
	int windowWidth;
	int windowHeight;
	int appStatus;
	list<GameObject*>* objectList;
	list<Processor*>* activeProcessors;
	
	list<Transmitter*>* activeTransmitters;
	CreationBase* base;

public:
	Reframing();
	~Reframing();

	void run();

private:
	void initSystems();
	void initShaders();
	void initCreations();
	void eventLoop();
	void inputProcess();
	void bypassProcessors();
	void redrawEverything();
};

