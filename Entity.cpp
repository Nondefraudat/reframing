#include "Entity.h"

// Constructors\Destructors

Entity::Entity(const char** title, const char** description)
{
	this->title			= title;
	this->description	= description;
}

// Getters

const char** Entity::getTitle()
{
	return title;
}
const char** Entity::getDescription()
{
	return nullptr;
}

// Setters

void Entity::setTitle(const char** title)
{
	this->title = title;
}
void Entity::setDescription(const char** description)
{
	this->description = description;
}

