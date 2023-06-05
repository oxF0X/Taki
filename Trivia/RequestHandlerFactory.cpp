#include "RequestHandlerFactory.h"

class LoginRequestHandler;


RequestHandlerFactory::RequestHandlerFactory(IDatabase* db): m_database(db), m_loginManager(LoginManager::getLoginManager(db))
{

}

RequestHandlerFactory::~RequestHandlerFactory()
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
	return this->m_roomMangager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(user, this->m_roomMangager, *this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room room)
{
	return new RoomMemberRequestHandler(user, room, this->m_roomMangager, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room room)
{
	return new RoomAdminRequestHandler(user, room, this->m_roomMangager, *this);
}



