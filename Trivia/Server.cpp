#include "Server.h"


Server::Server(IDatabase* db):m_database(db), m_handlerFactory(RequestHandlerFactory::getFactory(db)), m_comunicator(Comunicator::getComunicator(m_handlerFactory))
{

}

Server& Server::getServer(IDatabase* db)
{
	static Server s(db);
	return s;
}

void Server::run()
{
	std::thread t (&Comunicator::startHandleRequests, this->m_comunicator);
	t.detach();

	std::string cmd = "";
	while (cmd != "EXIT")
	{
		std::getline(std::cin, cmd);
	}
}

Server::~Server()
{

}
