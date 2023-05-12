#include "RequestHandlerFactory.h"

class LoginRequestHandler;

bool RequestHandlerFactory::is_exsit = false;

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db): m_database(db), m_loginManager(LoginManager::getLoginManager(db))
{
	RequestHandlerFactory::is_exsit = true;
}

RequestHandlerFactory RequestHandlerFactory::getFactory(IDatabase* db)
{
	if (RequestHandlerFactory::is_exsit)
	{
		throw(std::runtime_error("Instance of this object is already exsit"));
	}
	return RequestHandlerFactory(db);
}

LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	RequestHandlerFactory::is_exsit = false;
}
