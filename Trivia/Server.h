#pragma once

#include "Comunicator.h"

class Server
{
public:
	//Server();
	void run();

private:
	Comunicator m_comunicator;
};