#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	LoginManager& getLoginManger();
	LoginRequestHandler* createLoginRequestHandler();


private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};

