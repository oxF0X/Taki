#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory getFactory(IDatabase* db);
	LoginManager& getLoginManger();
	LoginRequestHandler* createLoginRequestHandler();

	~RequestHandlerFactory();
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	static bool is_exsit;
	RequestHandlerFactory(IDatabase* db);
};

