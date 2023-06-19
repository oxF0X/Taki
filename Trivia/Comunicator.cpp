#include "Comunicator.h"

Comunicator::Comunicator(RequestHandlerFactory& handler): m_handlerFactory(handler)
{
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}

Comunicator::~Comunicator()
{
	for (std::pair<SOCKET, IRequestHandler*> client : this->m_clients)
	{
		closesocket(client.first);
		delete(client.second);
	}

	try
	{
		WSACleanup();
	}
	catch (...) {}
}

void Comunicator::startHandleRequests()
{
	this->bindAndListen();
}

Comunicator& Comunicator::getComunicator(RequestHandlerFactory& handler)
{
	static Comunicator c(handler);
	return c;
}

void Comunicator::bindAndListen()
{
	SOCKET client_socket;

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");

	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		this->acceptClient();
	}
}

void Comunicator::acceptClient()
{
	SOCKET clientSocket = accept(this->m_serverSocket, NULL, NULL);

	if (clientSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client

	this->m_clients[clientSocket] = this->m_handlerFactory.createLoginRequestHandler();
	std::thread t(&Comunicator::handleNewClient, this, clientSocket);
	t.detach();
}

void Comunicator::handleNewClient(SOCKET socket)
{
	int msgCode, msgSize;
	std::vector<uint8_t> msg;

	while (true)
	{
		try
		{
			msgCode = Helper::getIntPartFromSocket(socket, CODE_SIZE);
			msgSize = Helper::getIntPartFromSocket(socket, LENGTH_SIZE);
			msg = msgSize? Helper::getDataFromSocket(socket, msgSize) : std::vector<uint8_t>();
		}
		catch (...)
		{
			this->disconnectUser(socket);
			return;
		}

		RequestInfo info{ msgCode, msg };

		if (!this->m_clients[socket]->isRequestRelevant(info))
		{
			try
			{
				Helper::sendData(socket, JsonRequestPacketSerializer::serializeResponse(ErrorResponse{ "ERROR: Irelevant request.\n" }));
				continue;
			}
			catch (...)
			{
				this->disconnectUser(socket);
				return;
			}

		}
		

		RequestResult r = this->m_clients[socket]->handleRequest(info);
		if (r.newHandler)
		{
			delete this->m_clients[socket];
			this->m_clients[socket] = r.newHandler;
		}

		try
		{
			Helper::sendData(socket, r.buffer);
		}
		catch (...)
		{
			this->disconnectUser(socket);
			return;
		}
	}
}

void Comunicator::disconnectUser(SOCKET socket)
{
	if (typeid(MenuRequestHandler(LoggedUser(""), this->m_handlerFactory.getRoomManager(), (this->m_handlerFactory))) == typeid(*(this->m_clients[socket])))
	{

		((MenuRequestHandler*)this->m_clients[socket])->signout();
	}
	delete(this->m_clients[socket]);
	this->m_clients.erase(socket);
	closesocket(socket);
}



