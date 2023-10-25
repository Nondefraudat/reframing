#include "reframing.hpp"
#include <vector>

using namespace std;

Reframing::Reframing() noexcept {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Error
	}
	window = SDL_CreateWindow("Reframing", 640, 480,
			SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);
	if (!window) {
		// TODO: Error
	}
	render = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);
	if (!render) {
		// TODO: Error
	}
	SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
	const std::vector< SDL_Vertex > vertexies = {
		{ SDL_FPoint{ 0, 0 }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ 5, -7 }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
		{ SDL_FPoint{ 10, 0 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
	};
	Entity entity(vertexies, { 320, 240 });
	entityList.push_back(entity);
}

Reframing::~Reframing() noexcept {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Reframing::run() noexcept {
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_EVENT_KEY_DOWN)
			{
				processKeySym(event.key.keysym.sym);
			}
		}
		updateWindow();
	}
	return 0;
}

void Reframing::updateWindow() noexcept {
	SDL_RenderClear(render);
	for (const Entity& entity : entityList) {
		const Vertexies verts = entity.getVertexies();
		SDL_RenderGeometry(render, nullptr, 
				verts.data(), verts.size(), nullptr, 0);
	}
	SDL_RenderPresent(render);
}

void Reframing::processKeySym(const SDL_Keycode keySym) noexcept {
	SDL_FPoint move { 0, 0 };
	const size_t speed = 5;
	switch (keySym) {
		case SDLK_LEFT: {
			move.x -= speed;
			break;
		}
		case SDLK_RIGHT: {
			move.x += speed;
			break;
		}
		case SDLK_UP: {
			move.y -= speed;
			break;
		}
		case SDLK_DOWN: {
			move.y += speed;
			break;
		}
	}
	for (Entity& entity : entityList) {
		SDL_FPoint position = entity.getPosition();
		position.x += move.x;
		position.y += move.y;
		entity.setPosition(position);
	}
}

