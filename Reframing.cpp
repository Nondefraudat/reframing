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
	Creation* creation; Base* base; Chassis* chassis;
	for (int i = 0; i < 5; i++)
	{
		creation = creationMaster->generateCreation(0);
		lastFrame->next = new Node<Frame>(creation);
		lastFrame->next->prev = lastFrame;
		lastFrame = lastFrame->next;

		BaseMaster* baseMaster = new BaseMaster(windowWidth, windowHeight);
		AccessoryMaster* accessoryMaster = new AccessoryMaster(windowWidth, windowHeight);
		ChassisMaster* chassisMaster = new ChassisMaster(windowWidth, windowHeight);
		ContactWeaponMaster* contactWeaponMaster = new ContactWeaponMaster(windowWidth, windowHeight);

		base = baseMaster->generateBase(0, creation);
		Accessory* accessory = accessoryMaster->generateAccessory(0, creation);
		chassis = chassisMaster->generateChassis(0, creation);

		base->connect(1, accessory);
		base->connect(2, chassis);

		creation->addBase(base);
		creation->addPart(base);

		creation->addChassis(chassis);
		creation->addPart(chassis);

		creation->addPart(accessory);

		ContactWeapon* contactWeapon = contactWeaponMaster->generateContactWeapon(0, creation);
		creation->addPart(contactWeapon);
		base->connect(3, contactWeapon);

		creation->spawnInXY((double)(rand() % 200 - 100) / 100, (double)(rand() % 200 - 100) / 100);
		
		userFrame = creation;
	}

	EnvironmentMaster* environmentMaster = new EnvironmentMaster(windowWidth, windowHeight);

	envirenment = environmentMaster->generateEnvirenment(0);
	lastFrame->next = new Node<Frame>(envirenment);
	lastFrame->next->prev = lastFrame;
	lastFrame = lastFrame->next;

	DecorationMaster* decorationMaster = new DecorationMaster(windowWidth, windowHeight);
	Decoration* decoration = decorationMaster->generateDecoration(0, envirenment);
	envirenment->addPart(decoration);
	envirenment->spawnInXY(0, -0.9);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(0); decoration->setY(-0.95);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(0); decoration->setY(-1.0);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(1.6); decoration->setY(-0.2);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(1.0); decoration->setY(0.3);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(-0.9); decoration->setY(0.2);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(1.4); decoration->setY(-0.85);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(-1.4); decoration->setY(-0.85);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(1.4); decoration->setY(-0.8);
	envirenment->addPart(decoration);

	decoration = decorationMaster->generateDecoration(0, envirenment);
	decoration->setX(-1.4); decoration->setY(-0.8);
	envirenment->addPart(decoration);
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
			// userFrame->spawnInXY(x_u, y_u);
			break;

		case SDL_MOUSEBUTTONDOWN:
			((Creation*)userFrame)->jump(firstFrame);
			break;
		default:
			break;
		}
	}
}

int lol[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double* x = new double[11];
double* y = new double[11];

void Reframing::redrawEverything()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Node<Frame>* currentFrame = firstFrame;
	int i = 0;
	while (currentFrame->next)
	{
		currentFrame = currentFrame->next;
		if (currentFrame->value != userFrame)
		{
			glColor3d(0.0, 0.0, 0.0);
			currentFrame->value->showAll();
		}
		else
		{
			glColor3d(0.0, 0.0, 0.4);
			currentFrame->value->showAll();
		}
		
		if (currentFrame->value != envirenment)
		{
			if (currentFrame->value != userFrame)
			{
				currentFrame->value->moveToXY(x[i], y[i], firstFrame);
				((Creation*)currentFrame->value)->jump(firstFrame);
			}
			else
			{
				currentFrame->value->moveToXY(x_u, y_u, firstFrame);
			}
		}
		if (lol[i])
		{
			lol[i]--;
		}
		else
		{
			lol[i] = rand() % 200 + 150;
			x[i] = (double)(rand() % 400 - 200) / 100;
			y[i] = (double)(rand() % 400 - 200) / 100;
		}
		i++;
	}

	SDL_GL_SwapWindow(window);
}
