#pragma once

#include "ItemTags.h"

class GameObject
{
	int x;
	int y;
	int width;
	int height;

protected:
	int itemTag;

public:
	GameObject(int x, int y, int width, int height);
	~GameObject();

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getItemTag();

	void setX(int x);
	void setY(int y);
};

