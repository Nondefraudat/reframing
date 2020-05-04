#pragma once



#include "CreationBase.h"
#include "Processor.h"
#include "Transmitter.h"
#include "Chassis.h"

using namespace std;

class Creation
{
	list<GameObject*>* parts;
	list<Processor*>* processors;
	list<Transmitter*>* transmitters;

public:
	Creation(int x, int y);
	~Creation();

	list<GameObject*>* getPartList();
	list<Processor*>* getProcessors();
	list<Transmitter*>* getTransmitters();
};

