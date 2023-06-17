#include "RequestHandlerFactory.h"

class LoginRequestHandler;


RequestHandlerFactory::RequestHandlerFactory(IDatabase* db): m_database(db), m_loginManager(LoginManager::getLoginManager(db))
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

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

RoomManager& RequestHandlerFactory::getRoomManager() 
{
	return this->m_roomMangager;
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}
