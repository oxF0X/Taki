#include "Server.h"

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
