#pragma once

#include "LoginManager.h"
#include "StatisticsManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "GameManager.h"


class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class GameRequestHandler;

// This class are responsible for the all Situations that exist in the game
class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getFactory(IDatabase* db);
	LoginManager& getLoginManger();
	RoomManager& getRoomManager();
	GameManager& getGameManger();
	StatisticsManager& getStatisticsManager();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser& user, Room& room);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& user, Room& room);
	GameRequestHandler* createGameRequestHandler(LoggedUser user, Game& game);
	

	~RequestHandlerFactory();
private:
	RequestHandlerFactory(IDatabase* db);
	RoomManager& m_roomManager;
	LoginManager& m_loginManager;
	GameManager& m_gameManager;
	StatisticsManager m_statisticsManager;
	IDatabase* m_database;
	static bool is_exsit;
};

