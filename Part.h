#pragma once

#include "ConnectorList.h"

class Part
{
private:
	int width;
	int height;
	int cpuUsage;
	ConnectorList ports;
	ConnectorList sockets;

public:
	Part(int width, int height, ConnectorList ports, ConnectorList sockets);
	~Part();

	int getWidth();
	int getHeight();
	int getCPUUsage();
	ConnectorList getPorts();
	ConnectorList getSockets();
};

