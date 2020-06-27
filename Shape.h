#pragma once

#include "GL/glew.h"

class Shape
{
	GLuint vboID;

	int viewCount;
	int vertexCount;
	
	double** vertexData;
	double** vertexDataRev;

	double* activeShape;
	double* activeShapeRev;

	double* vertexDataOutput;

	int activePhase;
	int currentView;
	int currentPhaseStage;
	int phaseChangingSpeed;

	double* phaseDifferences;

	bool phisical;

	double radius;

	int windowWidth;
	int windowHeight;

	int phaseCount;
	int* viewChangeOrderCounts;
	int** viewChangeOrders;

public:
	Shape(int viewCount, int vertexCount, int** vertexDataPxl, int phaseCount, int* viewChangeOrderCounts, int** viewChangeOrders, int windowWidth, int windowHeight);
	~Shape();

	void draw(double x, double y, int phase, bool reverse = false);

	bool diffusion(Shape* shape, double factorX, double factorY);

protected:
	void phaseChanging(int phase);
};

