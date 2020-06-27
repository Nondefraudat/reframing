#include "ShapeMaster.h"

ShapeMaster::ShapeMaster(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	maxShapeIndex = 5;

	viewCountPres = new int[maxShapeIndex];
	vertexCountPres = new int[maxShapeIndex];
	vertexDataPxlPres = new int**[maxShapeIndex]; 
	phaseCountPres = new int[maxShapeIndex];
	viewChangeOrderCountsPres = new int*[maxShapeIndex];
	viewChangeOrdersPres = new int**[maxShapeIndex];

	viewCountPres[0] = 1;
	vertexCountPres[0] = 12;
	vertexDataPxlPres[0] = new int* [viewCountPres[0]];
	{
		vertexDataPxlPres[0][0] = new int[vertexCountPres[0] * 2];
		{
			vertexDataPxlPres[0][0][0] = -10;
			vertexDataPxlPres[0][0][1] = 15;

			vertexDataPxlPres[0][0][2] = 10;
			vertexDataPxlPres[0][0][3] = 15;

			vertexDataPxlPres[0][0][4] = -20;
			vertexDataPxlPres[0][0][5] = -5;
		}
		{
			vertexDataPxlPres[0][0][6] = 10;
			vertexDataPxlPres[0][0][7] = 15;

			vertexDataPxlPres[0][0][8] = 20;
			vertexDataPxlPres[0][0][9] = -5;

			vertexDataPxlPres[0][0][10] = -20;
			vertexDataPxlPres[0][0][11] = -5;
		}
		{
			vertexDataPxlPres[0][0][12] = -20;
			vertexDataPxlPres[0][0][13] = -5;

			vertexDataPxlPres[0][0][14] = 20;
			vertexDataPxlPres[0][0][15] = -5;

			vertexDataPxlPres[0][0][16] = -10;
			vertexDataPxlPres[0][0][17] = -15;
		}
		{
			vertexDataPxlPres[0][0][18] = 20;
			vertexDataPxlPres[0][0][19] = -5;

			vertexDataPxlPres[0][0][20] = 10;
			vertexDataPxlPres[0][0][21] = -15;

			vertexDataPxlPres[0][0][22] = -10;
			vertexDataPxlPres[0][0][23] = -15;
		}
	}
	phaseCountPres[0] = 1;
	viewChangeOrderCountsPres[0] = new int [phaseCountPres[0]];
	{
		viewChangeOrderCountsPres[0][0] = 1;
	}
	viewChangeOrdersPres[0] = new int* [phaseCountPres[0]];
	{
		viewChangeOrdersPres[0][0] = new int[viewChangeOrderCountsPres[0][0]];
		{
			viewChangeOrdersPres[0][0][0] = 0;
		}
	}

	viewCountPres[1] = 2;
	vertexCountPres[1] = 12;
	vertexDataPxlPres[1] = new int* [viewCountPres[1]];
	{
		vertexDataPxlPres[1][0] = new int[vertexCountPres[1] * 2];
		{
			vertexDataPxlPres[1][0][0] = -1;
			vertexDataPxlPres[1][0][1] = 35;

			vertexDataPxlPres[1][0][2] = 1;
			vertexDataPxlPres[1][0][3] = 35;

			vertexDataPxlPres[1][0][4] = -1;
			vertexDataPxlPres[1][0][5] = 25;
		}
		{
			vertexDataPxlPres[1][0][6] = 1;
			vertexDataPxlPres[1][0][7] = 35;

			vertexDataPxlPres[1][0][8] = 1;
			vertexDataPxlPres[1][0][9] = 25;

			vertexDataPxlPres[1][0][10] = -1;
			vertexDataPxlPres[1][0][11] = 25;
		}
		{
			vertexDataPxlPres[1][0][12] = -1;
			vertexDataPxlPres[1][0][13] = 25;

			vertexDataPxlPres[1][0][14] = 1;
			vertexDataPxlPres[1][0][15] = 25;

			vertexDataPxlPres[1][0][16] = -1;
			vertexDataPxlPres[1][0][17] = 15;
		}
		{
			vertexDataPxlPres[1][0][18] = 1;
			vertexDataPxlPres[1][0][19] = 25;

			vertexDataPxlPres[1][0][20] = 1;
			vertexDataPxlPres[1][0][21] = 15;

			vertexDataPxlPres[1][0][22] = -1;
			vertexDataPxlPres[1][0][23] = 15;
		}
	}
	{
		vertexDataPxlPres[1][1] = new int[vertexCountPres[1] * 2];
		{
			vertexDataPxlPres[1][1][0] = -20;
			vertexDataPxlPres[1][1][1] = 29;

			vertexDataPxlPres[1][1][2] = -20;
			vertexDataPxlPres[1][1][3] = 31;

			vertexDataPxlPres[1][1][4] = -10;
			vertexDataPxlPres[1][1][5] = 24;
		}
		{
			vertexDataPxlPres[1][1][6] = -20;
			vertexDataPxlPres[1][1][7] = 31;

			vertexDataPxlPres[1][1][8] = -10;
			vertexDataPxlPres[1][1][9] = 26;

			vertexDataPxlPres[1][1][10] = -10;
			vertexDataPxlPres[1][1][11] = 24;
		}
		{
			vertexDataPxlPres[1][1][12] = -10;
			vertexDataPxlPres[1][1][13] = 24;

			vertexDataPxlPres[1][1][14] = -10;
			vertexDataPxlPres[1][1][15] = 26;

			vertexDataPxlPres[1][1][16] = 0;
			vertexDataPxlPres[1][1][17] = 1;
		}
		{
			vertexDataPxlPres[1][1][18] = -10;
			vertexDataPxlPres[1][1][19] = 26;

			vertexDataPxlPres[1][1][20] = 1;
			vertexDataPxlPres[1][1][21] = -1;

			vertexDataPxlPres[1][1][22] = 0;
			vertexDataPxlPres[1][1][23] = 1;
		}
	}
	phaseCountPres[1] = 2;
	viewChangeOrderCountsPres[1] = new int[phaseCountPres[1]];
	{
		viewChangeOrderCountsPres[1][0] = 1;
		viewChangeOrderCountsPres[1][1] = 2;
	}
	viewChangeOrdersPres[1] = new int* [phaseCountPres[1]];
	{
		viewChangeOrdersPres[1][0] = new int[viewChangeOrderCountsPres[1][0]];
		{
			viewChangeOrdersPres[1][0][0] = 0;
		}
		viewChangeOrdersPres[1][1] = new int[viewChangeOrderCountsPres[1][1]];
		{
			viewChangeOrdersPres[1][1][0] = 1;
			viewChangeOrdersPres[1][1][1] = 0;
		}
	}

	viewCountPres[2] = 2;
	vertexCountPres[2] = 12;
	vertexDataPxlPres[2] = new int* [viewCountPres[2]];
	{
		vertexDataPxlPres[2][0] = new int[vertexCountPres[2] * 2];
		{
			vertexDataPxlPres[2][0][0] = -20;
			vertexDataPxlPres[2][0][1] = 5;

			vertexDataPxlPres[2][0][2] = 0;
			vertexDataPxlPres[2][0][3] = 5;

			vertexDataPxlPres[2][0][4] = -10;
			vertexDataPxlPres[2][0][5] = -25;
		}
		{
			vertexDataPxlPres[2][0][6] = 10;
			vertexDataPxlPres[2][0][7] = -5;

			vertexDataPxlPres[2][0][8] = 20;
			vertexDataPxlPres[2][0][9] = 5;

			vertexDataPxlPres[2][0][10] = 30;
			vertexDataPxlPres[2][0][11] = -25;
		}
		{
			vertexDataPxlPres[2][0][12] = -20;
			vertexDataPxlPres[2][0][13] = 5;

			vertexDataPxlPres[2][0][14] = -10;
			vertexDataPxlPres[2][0][15] = -5;

			vertexDataPxlPres[2][0][16] = -30;
			vertexDataPxlPres[2][0][17] = -25;
		}
		{
			vertexDataPxlPres[2][0][18] = 0;
			vertexDataPxlPres[2][0][19] = 5;

			vertexDataPxlPres[2][0][20] = 20;
			vertexDataPxlPres[2][0][21] = 5;

			vertexDataPxlPres[2][0][22] = 10;
			vertexDataPxlPres[2][0][23] = -25;
		}
	}
	{
		vertexDataPxlPres[2][1] = new int[vertexCountPres[2] * 2];
		{
			vertexDataPxlPres[2][1][0] = -20;
			vertexDataPxlPres[2][1][1] = 5;

			vertexDataPxlPres[2][1][2] = -10;
			vertexDataPxlPres[2][1][3] = -5;

			vertexDataPxlPres[2][1][4] = -30;
			vertexDataPxlPres[2][1][5] = -25;
		}
		{
			vertexDataPxlPres[2][1][6] = 0;
			vertexDataPxlPres[2][1][7] = 5;

			vertexDataPxlPres[2][1][8] = 20;
			vertexDataPxlPres[2][1][9] = 5;

			vertexDataPxlPres[2][1][10] = 10;
			vertexDataPxlPres[2][1][11] = -25;
		}
		{
			vertexDataPxlPres[2][1][12] = -20;
			vertexDataPxlPres[2][1][13] = 5;

			vertexDataPxlPres[2][1][14] = 0;
			vertexDataPxlPres[2][1][15] = 5;

			vertexDataPxlPres[2][1][16] = -10;
			vertexDataPxlPres[2][1][17] = -25;
		}
		{
			vertexDataPxlPres[2][1][18] = 10;
			vertexDataPxlPres[2][1][19] = -5; 
		
			vertexDataPxlPres[2][1][20] = 20;
			vertexDataPxlPres[2][1][21] = 5;

			vertexDataPxlPres[2][1][22] = 30;
			vertexDataPxlPres[2][1][23] = -25;
		}
	}
	phaseCountPres[2] = 2;
	viewChangeOrderCountsPres[2] = new int[phaseCountPres[2]];
	{
		viewChangeOrderCountsPres[2][0] = 1;
		viewChangeOrderCountsPres[2][1] = 2;
	}
	viewChangeOrdersPres[2] = new int* [phaseCountPres[2]];
	{
		viewChangeOrdersPres[2][0] = new int[viewChangeOrderCountsPres[2][0]];
		{
			viewChangeOrdersPres[2][0][0] = 0;
		}
		viewChangeOrdersPres[2][1] = new int[viewChangeOrderCountsPres[2][1]];
		{
			viewChangeOrdersPres[2][1][0] = 1;
			viewChangeOrdersPres[2][1][1] = 0;
		}
	}

	viewCountPres[3] = 1;
	vertexCountPres[3] = 6;
	vertexDataPxlPres[3] = new int* [viewCountPres[3]];
	{
		vertexDataPxlPres[3][0] = new int[vertexCountPres[3] * 2];
		{
			vertexDataPxlPres[3][0][0] = -960;
			vertexDataPxlPres[3][0][1] = 15;

			vertexDataPxlPres[3][0][2] = 960;
			vertexDataPxlPres[3][0][3] = 15;

			vertexDataPxlPres[3][0][4] = -960;
			vertexDataPxlPres[3][0][5] = -15;
		}
		{
			vertexDataPxlPres[3][0][6] = 960;
			vertexDataPxlPres[3][0][7] = 15;

			vertexDataPxlPres[3][0][8] = -960;
			vertexDataPxlPres[3][0][9] = -15;

			vertexDataPxlPres[3][0][10] = 960;
			vertexDataPxlPres[3][0][11] = -15;
		}
	}
	phaseCountPres[3] = 1;
	viewChangeOrderCountsPres[3] = new int[phaseCountPres[3]];
	{
		viewChangeOrderCountsPres[3][0] = 1;
	}
	viewChangeOrdersPres[3] = new int* [phaseCountPres[3]];
	{
		viewChangeOrdersPres[3][0] = new int[viewChangeOrderCountsPres[3][0]];
		{
			viewChangeOrdersPres[3][0][0] = 0;
		}
	}

	viewCountPres[4] = 2;
	vertexCountPres[4] = 12;
	vertexDataPxlPres[4] = new int* [viewCountPres[4]];
	{
		vertexDataPxlPres[4][0] = new int[vertexCountPres[4] * 2];
		{
			vertexDataPxlPres[4][0][0] = -15;
			vertexDataPxlPres[4][0][1] = -10;

			vertexDataPxlPres[4][0][2] = -5;
			vertexDataPxlPres[4][0][3] = -10;

			vertexDataPxlPres[4][0][4] = -10;
			vertexDataPxlPres[4][0][5] = -25;
		}
		{
			vertexDataPxlPres[4][0][6] = 20;
			vertexDataPxlPres[4][0][7] = -15;

			vertexDataPxlPres[4][0][8] = 25;
			vertexDataPxlPres[4][0][9] = -10;

			vertexDataPxlPres[4][0][10] = 30;
			vertexDataPxlPres[4][0][11] = -25;
		}
		{
			vertexDataPxlPres[4][0][12] = -25;
			vertexDataPxlPres[4][0][13] = -10;

			vertexDataPxlPres[4][0][14] = -20;
			vertexDataPxlPres[4][0][15] = -15;

			vertexDataPxlPres[4][0][16] = -30;
			vertexDataPxlPres[4][0][17] = -25;
		}
		{
			vertexDataPxlPres[4][0][18] = 5;
			vertexDataPxlPres[4][0][19] = -10;

			vertexDataPxlPres[4][0][20] = 15;
			vertexDataPxlPres[4][0][21] = -10;

			vertexDataPxlPres[4][0][22] = 10;
			vertexDataPxlPres[4][0][23] = -25;
		}
	}
	{
		vertexDataPxlPres[4][1] = new int[vertexCountPres[4] * 2];
		{
			vertexDataPxlPres[4][1][0] = -25;
			vertexDataPxlPres[4][1][1] = -10;

			vertexDataPxlPres[4][1][2] = -20;
			vertexDataPxlPres[4][1][3] = -15;

			vertexDataPxlPres[4][1][4] = -30;
			vertexDataPxlPres[4][1][5] = -25;
		}
		{
			vertexDataPxlPres[4][1][6] = 5;
			vertexDataPxlPres[4][1][7] = -10;

			vertexDataPxlPres[4][1][8] = 15;
			vertexDataPxlPres[4][1][9] = -10;

			vertexDataPxlPres[4][1][10] = 10;
			vertexDataPxlPres[4][1][11] = -25;
		}
		{
			vertexDataPxlPres[4][1][12] = -15;
			vertexDataPxlPres[4][1][13] = -10;

			vertexDataPxlPres[4][1][14] = -5;
			vertexDataPxlPres[4][1][15] = -10;

			vertexDataPxlPres[4][1][16] = -10;
			vertexDataPxlPres[4][1][17] = -25;
		}
		{
			vertexDataPxlPres[4][1][18] = 20;
			vertexDataPxlPres[4][1][19] = -15;

			vertexDataPxlPres[4][1][20] = 25;
			vertexDataPxlPres[4][1][21] = -10;

			vertexDataPxlPres[4][1][22] = 30;
			vertexDataPxlPres[4][1][23] = -25;
		}
	}
	phaseCountPres[4] = 2;
	viewChangeOrderCountsPres[4] = new int[phaseCountPres[2]];
	{
		viewChangeOrderCountsPres[4][0] = 1;
		viewChangeOrderCountsPres[4][1] = 2;
	}
	viewChangeOrdersPres[4] = new int* [phaseCountPres[2]];
	{
		viewChangeOrdersPres[4][0] = new int[viewChangeOrderCountsPres[2][0]];
		{
			viewChangeOrdersPres[4][0][0] = 0;
		}
		viewChangeOrdersPres[4][1] = new int[viewChangeOrderCountsPres[2][1]];
		{
			viewChangeOrdersPres[4][1][0] = 1;
			viewChangeOrdersPres[4][1][1] = 0;
		}
	}
}

Shape* ShapeMaster::generateShape(int shapeIndex)
{
	if (shapeIndex < maxShapeIndex)
	{
		return new Shape(viewCountPres[shapeIndex], vertexCountPres[shapeIndex], vertexDataPxlPres[shapeIndex], phaseCountPres[shapeIndex], 
			viewChangeOrderCountsPres[shapeIndex], viewChangeOrdersPres[shapeIndex], windowWidth, windowHeight);
	}
	return nullptr;
}
