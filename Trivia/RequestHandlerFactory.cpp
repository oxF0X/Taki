#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db): m_database(db), m_loginManager(db)
{
	
}

LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}
