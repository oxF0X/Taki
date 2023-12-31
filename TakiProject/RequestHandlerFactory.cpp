#include "RequestHandlerFactory.h"

class LoginRequestHandler;

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db), m_roomManager(RoomManager::getManager()), m_loginManager(LoginManager::getLoginManager(db)), m_gameManager(GameManager::getGameManager()), m_statisticsManager()
{

}



RequestHandlerFactory& RequestHandlerFactory::getFactory(IDatabase* db)
{
	static RequestHandlerFactory r(db);
	return r;
}

LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

GameManager& RequestHandlerFactory::getGameManger()
{
	return this->m_gameManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(user, this->m_roomManager, *this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room& room)
{
	return new RoomMemberRequestHandler(user, room, this->m_roomManager, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room& room)
{
	return new RoomAdminRequestHandler(user, room, this->m_roomManager, *this);
}


GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game& game)
{
	return new GameRequestHandler(user, game);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}



