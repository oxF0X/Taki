#pragma once

#include "Comunicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server
{
public:
	static Server getServer(IDatabase* db);
	void run();
	~Server();

private:
	Server(IDatabase* db);
	
	Comunicator m_comunicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	static bool is_exsit;
};