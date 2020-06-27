#pragma once

#include <cmath>

#include "ErrorMessage.h"
#include "Entity.h"
#include "ShapeMaster.h"
#include "Node.h"

// Frame class block

class Part;
class Characteristics;

class Frame : public Entity
{
	int identifier;
	
	int stat;

	double gravityMult;

protected:
	int phase;
	bool reverse;

	int windowWidth;
	int windowHeight;

	Node<Part>* firstPart, * lastPart;

public:
	Frame(const char** title, const char** description, int windowWidth, int windowHeight, double gravityMult);

	int getIdentifier();
	Node<Part>* getFirstNode();
	Node<Part>* getLastNode();

	void setIdentifier(int identifier);
	void setFirstNode(Node<Part>* firstNode);
	void setLastNode(Node<Part>* lastNode);

	void addPart(Part* part);
	void removePart(Part* part);
	void showAll();


	virtual void spawnInXY(double x, double y) = 0;
	virtual void moveToXY(double x, double y, Node<Frame>* firstFrame) = 0;

	Part* diffusion(Node<Frame>* firstNode);
};


// Part class block

class LinkSystem;
class Shape;

class Part : public Entity
{
	LinkSystem* linkSystem;
	Shape* shape;

	double x;
	double xRev;
	double y;

	Frame* frame;
	Frame* defaultFrame;

public:
	Part(const char** title, const char** description, LinkSystem* linkSystem, Shape* shape, Frame* defaultFrame);

	LinkSystem* getLinkSystem();

	double getX();
	double getY();

	Shape* getShape();

	void setLinkSystem(LinkSystem* linkSystem);

	void setX(double x);
	void setY(double y);

	void connect(int portIndex, Part* connection);
	void show(int activePhase, bool reverse = false);

	bool diffusion(Part* part);
};


// LinkSystem class block

class Link;

class LinkSystem : public Entity
{
	int linkCount;

protected:
	Link** connectors;
	int callbackIndex;

public:
	LinkSystem(const char** title, const char** description, int linkCount, Link** connectors);

	int getLinkCount();
	Link** getConnectors();

	void setLinkCount(int linkCount);
	void setConnectors(Link** connectors);

	void addConnection(int linkIndex, Part* connection, Part* callback);
};


// Link class block

class Link : public Entity 
{
	int identifier;
	Part* connection;

	int horizontalDisplacementPxl;
	int verticalDisplacementPxl;

	double horizontalDisplacement;
	double horizontalDisplacementRev;
	double verticalDisplacement;

	int windowWidth;
	int windowHeight;

public:
	Link(const char** title, const char** description, int identifier, int horizontalDisplacementPxl, int verticalDisplacementPxl, int windowWidth, int windowHeight);

	int getIdentifier();
	Part* getConnection();

	double getHorizontalDisplacement();
	double getHorizontalDisplacementRev();
	double getVerticalDisplacement();

	void setIdentifier(int identifier);
	void setConnection(Part* connection);

	void setHorizontalDisplacement(double horizontalDisplacement);
	void setVerticalDisplacement(double verticalDisplacement);
};