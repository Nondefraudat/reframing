#include "entity.hpp"

Entity::Entity(const Vertexies& vertexies,
		const SDL_FPoint& position) noexcept
		: vertexies(vertexies), position(position) { }

SDL_FPoint Entity::getPosition() const noexcept {
	return position;
}

Vertexies Entity::getVertexies() const noexcept {
	Vertexies target;
	for (SDL_Vertex vertex : vertexies) {
		vertex.position.x += position.x;
		vertex.position.y += position.y;
		target.push_back(vertex);
	}
	return target;
}

void Entity::setPosition(const SDL_FPoint& position) noexcept {
	this->position = position;
}


