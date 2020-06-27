#include "Shape.h"

#include <iostream>

// Constructors\desctructors

Shape::Shape(int viewCount, int vertexCount, int** vertexDataPxl, int phaseCount, int* viewChangeOrderCounts, int** viewChangeOrders, int windowWidth, int windowHeight)
{
	this->viewCount = viewCount;
	this->vertexCount = vertexCount;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->phaseCount = phaseCount;
	this->viewChangeOrderCounts = viewChangeOrderCounts;
	this->viewChangeOrders = viewChangeOrders;
	
	vboID = 0;

	vertexData = new double*[phaseCount];
	for (int i = 0; i < phaseCount; i++)
	{
		vertexData[i] = new double[vertexCount * 2];
		for (int j = 0; j < vertexCount * 2; j++)
		{
			vertexData[i][j] = (double)(vertexDataPxl[i][j]) / windowWidth * 2;
			j++;
			vertexData[i][j] = (double)(vertexDataPxl[i][j]) / windowHeight * 2;
		}
	}

	vertexDataRev = new double* [phaseCount];
	for (int i = 0; i < phaseCount; i++)
	{
		vertexDataRev[i] = new double[vertexCount * 2];
		for (int j = 0; j < vertexCount * 2; j++)
		{
			vertexDataRev[i][j] = vertexData[i][j] * -1;
			j++;
			vertexDataRev[i][j] = vertexData[i][j];
		}
	}
	 
	activeShape = new double[vertexCount * 2];
	for (int i = 0; i < vertexCount * 2; i++)
	{
		activeShape[i] = vertexData[0][i];
	}

	activeShapeRev = new double[vertexCount * 2];
	for (int i = 0; i < vertexCount * 2; i++)
	{
		activeShapeRev[i] = vertexDataRev[0][i];
	}

	vertexDataOutput = new double[vertexCount * 2];

	activePhase = 0;
	currentView = 0;
	currentPhaseStage = 0;
	phaseChangingSpeed = 10;

	phaseDifferences = new double[vertexCount * 2];

	phisical = true;

	radius = 0.0;
	double counter;
	maxX = minX = activeShape[0];
	maxY = minY = activeShape[1];
	for (int i = 2; i < vertexCount * 2; i++)
	{
		if (activeShape[i] > maxX)
		{
			maxX = activeShape[i];
		}
		else
		{
			if (activeShape[i] < minX)
			{
				minX = activeShape[i];
			}
		}
		i++;
		if (activeShape[i] > maxY)
		{
			maxY = activeShape[i];
		}
		else
		{
			if (activeShape[i] < minY)
			{
				minY = activeShape[i];
			}
		}
	}
}
Shape::~Shape()
{
	glDeleteBuffers(1, &vboID);
}

// Getters



// Setters



// Methods

void Shape::draw(double x, double y, int phase, bool reverse)
{
	if (!vboID)
	{
		glGenBuffers(1, &vboID);
	}

	phaseChanging(phase);

	if (reverse)
	{
		for (int i = 0; i < vertexCount * 2; i++)
		{
			vertexDataOutput[i] = activeShapeRev[i] + x;
			i++;
			vertexDataOutput[i] = activeShapeRev[i] + y;
		}
	}
	else
	{
		for (int i = 0; i < vertexCount * 2; i++)
		{
			vertexDataOutput[i] = activeShape[i] + x;
			i++;
			vertexDataOutput[i] = activeShape[i] + y;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * vertexCount * 2, vertexDataOutput, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool Shape::diffusion(Shape* shape, double factorX, double factorY)
{
	double counter = sqrt(pow(factorX, 2) + pow(factorY, 2));
	if ((factorX <= maxX - shape->minX and factorX >= minX - shape->maxX) and (factorY <= maxY - shape->minY and factorY >= minY - shape->maxY) and phisical and shape->phisical)
	{
		for (int i = 0; i < vertexCount * 2; i += 6)
		{
			for (int j = 0; j < shape->vertexCount * 2; j += 2)
			{
				double x0 = shape->activeShape[j] + factorX;
				double x1 = activeShape[i];
				double x2 = activeShape[i + 2];
				double x3 = activeShape[i + 4];

				double y0 = shape->activeShape[j + 1] + factorY;
				double y1 = activeShape[i + 1];
				double y2 = activeShape[i + 3];
				double y3 = activeShape[i + 5];
				int counter = 0;

				double result = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}
				if (abs(counter) == 3)
				{
					return true;
				}
			}
		}

		for (int i = 0; i < shape->vertexCount * 2; i += 6)
		{
			for (int j = 0; j < vertexCount * 2; j += 2)
			{
				double x0 = activeShape[j] - factorX;
				double x1 = shape->activeShape[i];
				double x2 = shape->activeShape[i + 2];
				double x3 = shape->activeShape[i + 4];

				double y0 = activeShape[j + 1] - factorY;
				double y1 = shape->activeShape[i + 1];
				double y2 = shape->activeShape[i + 3];
				double y3 = shape->activeShape[i + 5];
				int counter = 0;

				double result = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}
				if (abs(counter) == 3)
				{
					return true;
				}
			}
		}

		return false;
		/*double min = sqrt(pow(shape->activeShape[0] + factorX - activeShape[0], 2) + pow(shape->activeShape[1] + factorY - activeShape[1], 2));
		double xValue_i = activeShape[0];
		double yValue_i = activeShape[1];
		double xValue_j = shape->activeShape[0];
		double yValue_j = shape->activeShape[1];
		for (int i = 2; i < vertexCount * 2; i += 2)
		{
			for (int j = 2; j < shape->vertexCount * 2; j += 2)
			{
				double range = sqrt(pow(shape->activeShape[j] + factorX - activeShape[i], 2) + pow(shape->activeShape[j + 1] + factorY - activeShape[i + 1], 2));
				if (range < min)
				{
					min = range;
					xValue_i = activeShape[i];
					yValue_i = activeShape[i + 1];
					xValue_j = shape->activeShape[j];
					yValue_j = shape->activeShape[j + 1];
				}
			}
		}
		for (int i = 0; i < vertexCount * 2; i += 2)
		{
			double result;
			if (xValue_i == activeShape[i] and yValue_i == activeShape[i + 1])
			{
				double x0 = xValue_j + factorX; 
				double x1 = activeShape[i - i % 6];
				double x2 = activeShape[i - i % 6 + 2];
				double x3 = activeShape[i - i % 6 + 4];
				
				double y0 = yValue_j + factorY;
				double y1 = activeShape[i - i % 6 + 1];
				double y2 = activeShape[i - i % 6 + 3];
				double y3 = activeShape[i - i % 6 + 5];

				int counter = 0;

				result = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}
				if (abs(counter) == 3)
				{
					return true;
				}
			}
		}

		for (int j = 0; j < shape->vertexCount * 2; j += 2)
		{
			double result;
			if (xValue_j == shape->activeShape[j] and yValue_j == shape->activeShape[j + 1])
			{
				double x0 = xValue_i - factorX;
				double x1 = shape->activeShape[j - j % 6];
				double x2 = shape->activeShape[j - j % 6 + 2];
				double x3 = shape->activeShape[j - j % 6 + 4];

				double y0 = yValue_i - factorY;
				double y1 = shape->activeShape[j - j % 6 + 1];
				double y2 = shape->activeShape[j - j % 6 + 3];
				double y3 = shape->activeShape[j - j % 6 + 5];

				int counter = 0;

				result = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}

				result = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);
				if (!result)
				{
					return true;
				}
				else
				{
					if (result > 0)
					{
						counter++;
					}
					else
					{
						counter--;
					}
				}
				if (abs(counter) == 3)
				{
					return true;
				}
			}
		}
		return false;
	*/
	}
	return false;
}

double Shape::getMaxX()
{
	return maxX;
}

double Shape::getMaxY()
{
	return maxY;
}

double Shape::getMinX()
{
	return minX;
}

double Shape::getMinY()
{
	return minY;
}

void Shape::setPhisical(bool value)
{
	phisical = value;
}


// Private methods
 
void Shape::phaseChanging(int phase)
{
	if (activePhase != phase and phase < phaseCount)
	{
		for (int i = 0; i < vertexCount * 2; i++)
		{
			phaseDifferences[i] = (vertexData[viewChangeOrders[phase][0]][i] - activeShape[i]) * ((double)currentPhaseStage / phaseChangingSpeed);
		}
		activePhase = phase;
		currentView = 0;
	}
	if (currentPhaseStage == phaseChangingSpeed)
	{
		currentView++;
		if (currentView == viewChangeOrderCounts[activePhase])
		{
			currentView = 0;
		}

		for (int i = 0; i < vertexCount * 2; i++)
		{
			phaseDifferences[i] = (vertexData[viewChangeOrders[activePhase][currentView]][i] - activeShape[i]) * ((double)1 / phaseChangingSpeed);
		}
		currentPhaseStage = 0;
	}
	if (currentPhaseStage < phaseChangingSpeed)
	{
		for (int i = 0; i < vertexCount * 2; i++)
		{

			if (abs(vertexData[viewChangeOrders[activePhase][currentView]][i] - activeShape[i]) < abs(phaseDifferences[i]))
			{
				activeShape[i] = vertexData[viewChangeOrders[activePhase][currentView]][i];
				activeShapeRev[i] = activeShape[i] * -1;
			}
			else
			{
				activeShape[i] += phaseDifferences[i];
				activeShapeRev[i] = activeShape[i] * -1;
			}
			i++;
			if (abs(vertexData[viewChangeOrders[activePhase][currentView]][i] - activeShape[i]) < abs(phaseDifferences[i]))
			{
				activeShape[i] = vertexData[viewChangeOrders[activePhase][currentView]][i];
				activeShapeRev[i] = activeShape[i];
			}
			else
			{
				activeShape[i] += phaseDifferences[i];
				activeShapeRev[i] = activeShape[i];
			}
		}
		currentPhaseStage++;
		maxX = minX = activeShape[0];
		maxY = minY = activeShape[1];
		for (int i = 2; i < vertexCount * 2; i++)
		{
			if (activeShape[i] > maxX)
			{
				maxX = activeShape[i];
			}
			else
			{
				if (activeShape[i] < minX)
				{
					minX = activeShape[i];
				}
			}
			i++;
			if (activeShape[i] > maxY)
			{
				maxY = activeShape[i];
			}
			else
			{
				if (activeShape[i] < minY)
				{
					minY = activeShape[i];
				}
			}
		}
	}
}
