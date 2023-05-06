#include "Server.h"



Server::Server(IDatabase* db):m_database(db), m_handlerFactory(db), m_comunicator(m_handlerFactory)
{
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
