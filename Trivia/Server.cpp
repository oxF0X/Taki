#include "Server.h"

bool Server::is_exsit = false;

Server::Server(IDatabase* db):m_database(db), m_handlerFactory(RequestHandlerFactory::getFactory(db)), m_comunicator(Comunicator::getComunicator(m_handlerFactory))
{
	Server::is_exsit = true;
}

Server Server::getServer(IDatabase* db)
{
	if (Server::is_exsit)
	{
		throw(std::runtime_error("Instance of this object is already exsit"));
	}
	return Server(db);
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
	Server::is_exsit = false;
}
