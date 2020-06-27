#pragma once

#include "Shape.h"

class ShapeMaster
{
	int maxShapeIndex;

	int* phaseCountPres;
	int* viewCountPres;
	int* vertexCountPres;
	int*** vertexDataPxlPres;

	int** viewChangeOrderCountsPres;
	int*** viewChangeOrdersPres;

	int windowWidth;
	int windowHeight;

public:
	ShapeMaster(int windowWidth, int windowHeight);

	Shape* generateShape(int shapeIndex);
};

