#pragma once

#include "Comunicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Server
{
public:
	static Server& getServer(IDatabase* db);
	void run();
	~Server();

private:
	Server(IDatabase* db);
	
	RequestHandlerFactory& m_handlerFactory;
	IDatabase* m_database;
	Comunicator& m_comunicator;
};