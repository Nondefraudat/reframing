#include "Reframing.h"

Reframing::Reframing()
{
	window = nullptr;
	windowWidth = 1920;
	windowHeight = 1080;
	appStatus = AS_OFF;
	objectList = new list<GameObject*>;
	// activeProcessors = new list<Processor*>;
} 

Reframing::~Reframing()
{

}

void Reframing::run()
{
	appStatus = AS_ON;
	initSystems();
	initShaders();
	initCreations();
	eventLoop();
}

void Reframing::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	glewInit();
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	glClearColor(0, 0, 0, 1.0);
}

void Reframing::initShaders()
{
	/* =)) */
}

void Reframing::initCreations()
{
	Creation* creation = new Creation(0, 0);
	objectList = creation->getPartList();
	activeProcessors = creation->getProcessors();
	activeTransmitters = creation->getTransmitters();
}

void Reframing::eventLoop()
{
	while (appStatus)
	{
		inputProcess();
		bypassProcessors();
		redrawEverything();
	}
}

void Reframing::inputProcess()
{
	static SDL_Event sdlEvent;

	list<Transmitter*>::iterator it;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.scancode)
			{
			case SDL_SCANCODE_LEFT:
				for (it = activeTransmitters->begin(); it != activeTransmitters->end(); it++)
				{
					(*it)->setOperation(OL_MOVE_TOLEFT);
				}
				break;
			case SDL_SCANCODE_RIGHT:
				for (it = activeTransmitters->begin(); it != activeTransmitters->end(); it++)
				{
					(*it)->setOperation(OL_MOVE_TORIGHT);
				}
				break;
			case SDL_SCANCODE_UP:
				for (it = activeTransmitters->begin(); it != activeTransmitters->end(); it++)
				{
					(*it)->setOperation(OL_MOVE_TOUP);
				}
				break;
			case SDL_SCANCODE_DOWN:
				for (it = activeTransmitters->begin(); it != activeTransmitters->end(); it++)
				{
					(*it)->setOperation(OL_MOVE_TODOWN);
				}
				break;
			default:
				for (it = activeTransmitters->begin(); it != activeTransmitters->end(); it++)
				{
					(*it)->setOperation(OL_PASS);
				}
				break;
			}
			break;
		case SDL_QUIT:
			appStatus = AS_OFF;
			break;
		}
	}
}

void Reframing::bypassProcessors()
{
	list<Processor*>::iterator it;
	for (it = activeProcessors->begin(); it != activeProcessors->end(); it++)
	{
		(*it)->work();
	}
}

void Reframing::redrawEverything()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);
	{
		double x1, x2;
		double y1, y2;
		list<GameObject*>::iterator it;
		for (it = objectList->begin(); it != objectList->end(); it++)
		{
			x1 = (double)(*it)->getX() / windowWidth * 2;
			y1 = (double)(*it)->getY() / windowHeight * 2;
			x2 = x1 + (double)(*it)->getWidth() / windowWidth * 2;
			y2 = y1 - (double)(*it)->getHeight() / windowHeight * 2;
		
			switch ((*it)->getItemTag())
			{
			case IT_BASE:
				glColor4d(1.0, 1.0, 0, 0.2);
				break;
			case IT_PROCESOR:
				glColor4d(1.0, 0, 0, 0.2);
				break;
			case IT_TRANSMITTER:
				glColor4d(0, 1.0, 1.0, 0.2);
				break;
			case IT_CHASSIS:
				glColor4d(0, 0, 1.0, 0.2);
				break;
			case IT_DEFAULT:
				glColor4d(0.6, 0.6, 0.6, 0.2);
				break;
			}
		
			glVertex2d(x1, y1);
			glVertex2d(x2, y1);
			glVertex2d(x1, y2);
		
			glVertex2d(x2, y1);
			glVertex2d(x1, y2);
			glVertex2d(x2, y2);
		}
	}
	glEnd();

	SDL_GL_SwapWindow(window);
}
