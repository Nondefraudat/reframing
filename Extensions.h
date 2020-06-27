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

	double horisontalSpeed;
	double verticalSpeed;

	double horisontalBoost;
	double verticalBoost;

	double maxHorisontalSpeed;
	double maxVerticalSpeed;

	double defaultHorisontalFactor;
	double defaultVerticalFactor;

	double gravitationFactor;
	double fallRate;
	
	double jumpPower;

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
	
	void horisontalMove(double distance, Node<Frame>* firstFrame);
	void verticalMove(double distance, Node<Frame>* firstFrame);

	void gravitation(Node<Frame>* firstFrame);

	void tryToGetOut(Node<Frame>* firstFrame);

	void jump(Node<Frame>* firstFrame);
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
	Base(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame,
		int defaultSpawnPointDisplacementPxlX, int defaultSpawnPointDisplacementPxlY, int windowWidth, int windowHeight);
};

class Chassis :
	public Part
{
	double horisontalBoostMult;
	double verticalBoostMult;

	double maxHorisontalSpeedMult;
	double maxVerticalSpeedMult;

	double horisontalBreakMult;
	double verticalBreakMult;

	double jumpPowerMult;

public:
	Chassis(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame,
		double horisontalBoostMult, double verticalBoostMult, 
		double maxHorisontalSpeedMult, double maxVerticalSpeedMult,
		double horisontalBreakMult, double verticalBreakMult,
		double jumpPowerMult);

	double getHorizontalBoostMult();
	double getVerticalBoostMult(); 
	
	double getMaxHorisontalSpeedMult();
	double getMaxVerticalSpeedMult();

	double getHorisontalBreakMult();
	double getVerticalBreakMult();

	double getJumpPowerMult();
};

class Accessory :
	public Part
{
public:
	Accessory(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame);

	bool diffusion(Part* part);
};

class Decoration :
	public Part
{
public:
	Decoration(const char** title, const char** description, double totalResistance, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame);
};

class ContactWeapon :
	public Part
{
	double contactDamageMult;

public:
	ContactWeapon(const char** title, const char** description, double totalResistance, double contactDamageMult, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame);

	void show(int activePhase, bool reverse);
};