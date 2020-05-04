#include "Creation.h"

Creation::Creation(int x, int y)
{
	parts = new list<GameObject*>;
	processors = new list<Processor*>;
	transmitters = new list<Transmitter*>;

	CreationBase* base;
	list<Connector*>* baseConnectors;
	Connector* baseConnector;

	Processor* processor;
	list<Connector*>* processorConnectors;
	Connector* processorConnector;

	Transmitter* transmitter;
	list<Connector*>* transmitterConnectors;
	Connector* transmitterConnector;

	Chassis* chassis;
	list<Connector*>* chassisConnectors;
	Connector* chassisConnector;

	base = new CreationBase(0, 0, 100, 20);
	parts->push_back(base);
	baseConnectors = new list<Connector*>;
	
	// Processor linking
	processor = new Processor(5, 5, base);
	parts->push_back(processor);
	processors->push_back(processor);
	processorConnectors = new list<Connector*>;

	baseConnector = new Connector(5, -5, base);
	baseConnectors->push_back(baseConnector);

	processorConnector = new Connector(0, 0, processor);
	processorConnectors->push_back(processorConnector);
	processor->setConnectors(processorConnectors);

	baseConnector->setLink(processorConnector);
	
	// Transmitter linking
	transmitter = new Transmitter(3, 50);
	parts->push_back(transmitter);
	transmitters->push_back(transmitter);
	transmitterConnectors = new list<Connector*>;

	baseConnector = new Connector(97, 0, base);
	baseConnectors->push_back(baseConnector);

	transmitterConnector = new Connector(0, -50, transmitter);
	transmitterConnectors->push_back(transmitterConnector);
	transmitter->setConnectors(transmitterConnectors);

	baseConnector->setLink(transmitterConnector);
	
	// Chassis linking
	chassis = new Chassis(110, 10, base);
	parts->push_back(chassis);
	chassisConnectors = new list<Connector*>;

	baseConnector = new Connector(-5, -22, base);
	baseConnectors->push_back(baseConnector);

	chassisConnector = new Connector(0, 0, chassis);
	chassisConnectors->push_back(chassisConnector);
	chassis->setConnectors(chassisConnectors);

	baseConnector->setLink(chassisConnector);

	// Final
	base->setConnectors(baseConnectors);
	base->setX(x);
	base->setY(y);
}

Creation::~Creation()
{

}

list<GameObject*>* Creation::getPartList()
{
	return parts;
}

list<Processor*>* Creation::getProcessors()
{
	return processors;
}

list<Transmitter*>* Creation::getTransmitters()
{
	return transmitters;
}
