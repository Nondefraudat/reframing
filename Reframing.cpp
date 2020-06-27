#include "Reframing.h"

// Constructors\destructors

Reframing::Reframing()
{
	window = nullptr;
	windowWidth = 1920;
	windowHeight = 1080;
	appStatus = AS_OFF;

	firstFrame = lastFrame = new Node<Frame>(nullptr);

	creationMaster = new CreationMaster(windowWidth, windowHeight);

	Node<Frame>* currentFrame = firstFrame;
	for (int i = 0; i < 6; i++)
	{
		Creation* creation = creationMaster->generateCreation(0);
		lastFrame->next = new Node<Frame>(creation);
		lastFrame->next->prev = lastFrame;
		lastFrame = lastFrame->next;

		BaseMaster* baseMaster = new BaseMaster(windowWidth, windowHeight);
		AccessoryMaster* accessoryMaster = new AccessoryMaster(windowWidth, windowHeight);
		ChassisMaster* chassisMaster = new ChassisMaster(windowWidth, windowHeight);

		Base* base = baseMaster->generateBase(0, creation);
		Accessory* accessory = accessoryMaster->generateAccessory(0, creation);
		Chassis* chassis = chassisMaster->generateChassis(0, creation);

		base->connect(1, accessory);
		base->connect(2, chassis);

		creation->addBase(base);
		creation->addPart(base);

		creation->addChassis(chassis);
		creation->addPart(chassis);

		creation->addPart(accessory);
		creation->spawnInXY((double)(rand() % 200 - 100) / 100, (double)(rand() % 200 - 100) / 100);
		
		userFrame = creation;
	}
}
Reframing::~Reframing()
{
	
}

// Public methods

void Reframing::run()
{
	appStatus = AS_ON;
	initSystems();
	initShaders();
	eventLoop();
}

// Private methods

void Reframing::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	glewInit();
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3d(0.0, 0.0, 0.0);
}
void Reframing::initShaders()
{
	/* Coming soon =] */
}
void Reframing::eventLoop()
{
	while (appStatus)
	{
		inputProcess();
		redrawEverything();
	}
}

double x_u;
double y_u;

void Reframing::inputProcess()
{
	static SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			appStatus = AS_OFF;
			break;

		case SDL_MOUSEMOTION:
			x_u = ((double)sdlEvent.motion.x - (double)0.5 * windowWidth) / windowWidth * 2;
			y_u = -((double)sdlEvent.motion.y - (double)0.5 * windowHeight) / windowHeight * 2;
			break;
		default:
			break;
		}
	}
}

int lol[] = { 0, 0, 0, 0, 0, 0 };
double* x = new double[6];
double* y = new double[6];

void Reframing::redrawEverything()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Node<Frame>* currentFrame = firstFrame;
	int i = 0;
	while (currentFrame->next)
	{
		currentFrame = currentFrame->next;
		currentFrame->value->showAll();
		
		if (currentFrame->value != userFrame)
		{
			currentFrame->value->moveToXY(x[i], y[i], firstFrame);
		}
		else
		{
			currentFrame->value->moveToXY(x_u, y_u, firstFrame);
		}
		if (lol[i])
		{
			lol[i]--;
		}
		else
		{
			lol[i] = rand() % 200 + 150;
			x[i] = (double)(rand() % 200 - 100) / 100;
			y[i] = (double)(rand() % 200 - 100) / 100;
		}
		i++;
	}

	SDL_GL_SwapWindow(window);
}
