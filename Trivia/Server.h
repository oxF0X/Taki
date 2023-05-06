#pragma once

#include "Comunicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server
{
public:
	//Server(IDatabase* database ,);
	void run();

private:
	Comunicator m_comunicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
};