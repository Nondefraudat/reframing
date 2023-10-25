#pragma once
#include <SDL3/SDL.h>
#include <vector>

using Vertexies = std::vector<SDL_Vertex>;

class Entity {
public:
	Entity(const Vertexies& vertexies,
			const SDL_FPoint& position = { 0, 0 }) noexcept;

	SDL_FPoint getPosition() const noexcept;
	Vertexies getVertexies() const noexcept;
	
	void setPosition(const SDL_FPoint& position) noexcept;

private:
	Vertexies vertexies;
	SDL_FPoint position;
};
