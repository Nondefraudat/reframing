#include "GameObject.h"

GameObject::GameObject(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	itemTag = IT_DEFAULT;
}

GameObject::~GameObject()
{

}

int GameObject::getX()
{
	return x;
}

int GameObject::getY()
{
	return y;
}

int GameObject::getWidth()
{
	return width;
}

int GameObject::getHeight()
{
	return height;
}

int GameObject::getItemTag()
{
	return itemTag;
}

void GameObject::setX(int x)
{
	this->x = x;
}

void GameObject::setY(int y)
{
	this->y = y;
}
