#include "Reframing.h"

Reframing::Reframing() {
	window.handler = nullptr;
	window.width = 1080;
	window.height = 1920;
	status = 0;
	input = nullptr;
}

Reframing::~Reframing() {

}

void Reframing::execute() {
	initialize();
	eventCycle();
}

void Reframing::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window.handler = SDL_CreateWindow("Reframing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.width, window.height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	SDL_GLContext glContext(SDL_GL_CreateContext(window.handler));
	glewInit();
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Reframing::eventCycle() {
	while (isExecuting()) {
		getInput();
		showChanges();
	}
}

void Reframing::getInput() {
	SDL_PollEvent(input);
	switch (input->type) {
	case SDL_QUIT:
		status = 1;
		break;
	default:
		break;
	}
}

void Reframing::showChanges() {
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(window.handler);
}

bool Reframing::isExecuting() {
	return status == 0;
}
