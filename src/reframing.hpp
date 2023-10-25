#pragma once
#include "entity.hpp"
#include <SDL3/SDL.h>
#include <list>

using EntityList = std::list<Entity>;

class Reframing {
public:
	Reframing() noexcept;
	~Reframing() noexcept;

	int run() noexcept;

private:
	SDL_Window* window;
	SDL_Renderer* render;
	EntityList entityList;

	void updateWindow() noexcept;
	void processKeySym(const SDL_Keycode keySym) noexcept;
};
