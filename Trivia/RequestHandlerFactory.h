#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "GameManager.h"


class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getFactory(IDatabase* db);
	LoginManager& getLoginManger();
	RoomManager& getRoomManager();
	GameManager& getGameManger();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser& user, Room& room);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& user, Room& room);
	GameRequestHandler* createGameRequestHandler(LoggedUser user, Room& room);
	

	~RequestHandlerFactory();
private:
	RequestHandlerFactory(IDatabase* db);
	RoomManager& m_roomManager;
	LoginManager& m_loginManager;
	GameManager& m_gameManager;
	IDatabase* m_database;
	static bool is_exsit;
};

