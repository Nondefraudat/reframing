#pragma once

#include "SDL/SDL.h"
#include "GL/glew.h"
#include "SDL/SDL.h"

class Reframing
{
private:
	struct Window { 
		SDL_Window* handler; int width, height; 
	} window;
	int status;
	SDL_Event* input;

public:
	Reframing();
	~Reframing();

	void execute();

private:
	void initialize();
	void eventCycle();
	void getInput();
	void showChanges();

	bool isExecuting();
};

