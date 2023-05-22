#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "IDatabase.h"
#include "RoomManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getFactory(IDatabase* db);
	LoginManager& getLoginManger();
	LoginRequestHandler* createLoginRequestHandler();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomManager& getRoomManager();
	~RequestHandlerFactory();
private:
	RequestHandlerFactory(IDatabase* db);
	RoomManager m_roomMangager;
	LoginManager m_loginManager;
	IDatabase* m_database;
	static bool is_exsit;
};

