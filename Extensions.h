#pragma once

#include "Pieces.h"

// Frame extensions

class Base;
class Chassis;

class Creation :
	public Frame
{
	double defaultSpawnPointX;
	double defaultSpawnPointY;

	Node<Base>* firstBase, * lastBase;
	Node<Chassis>* firstChassis, * lastChassis;

public:
	Creation(const char** title, const char** description, int windowWidth, int windowHeight, double gravityMult, int defaultSpawnPointXPxl, int defaultSpawnPointYPxl);

	void addBase(Base* base);
	void addChassis(Chassis* chassis);

	void removeBase(Base* base);
	void removeChassis(Chassis* chassis);

	void spawnInXY(double x, double y);

	void moveToXY(double x, double y, Node<Frame>* firstFrame);
	
	void moveToRight(Node<Frame>* firstFrame);
	void moveToLeft(Node<Frame>* firstFrame);
	void moveToUp(Node<Frame>* firstFrame);
	void moveToDown(Node<Frame>* firstFrame);

	void jump();
};

class Environment :
	public Frame
{
public:
	Environment(const char** title, const char** description, int windowWidth, int windowHeight, double gravityMult);

	void moveToXY(double x, double y, Node<Frame>* firstFrame);
	void spawnInXY(double x, double y);
};

// Part extensions

class Base :
	public Part
{
	double defaultSpawnPointDisplacementX;
	double defaultSpawnPointDisplacementY;

public:
	Base(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame,
		int defaultSpawnPointDisplacementPxlX, int defaultSpawnPointDisplacementPxlY, int windowWidth, int windowHeight);
};

class Chassis :
	public Part
{
	double horisontalSpeedMult;
	double verticalSpeedMult;

public:
	Chassis(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame, double horisontalSpeedMult, double verticalSpeedMult);

	double getHorizontalSpeedMult();
	double getVerticalSpeedMult();
};

class Accessory :
	public Part
{
public:
	Accessory(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame);

	bool diffusion(Part* part);
};
