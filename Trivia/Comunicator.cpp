#include "Comunicator.h"

Comunicator::Comunicator()
{
	WSADATA wsaData;
	int wsaret = WSAStartup(0x0202, &wsaData);
	if (wsaret != 0)
	{
		throw std::exception(std::runtime_error("WSAStartup failed"));
	}

	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}

Comunicator::~Comunicator()
{
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

	this->m_clients[clientSocket] = LoginRequestHandler();
	std::thread t(&Comunicator::handleNewClient, this, clientSocket);
	t.detach();
}

void Comunicator::handleNewClient(SOCKET socket)
{
	char headers[HEADERS_SIZE];

	//if (send(socket, data, 5 , 0) == INVALID_SOCKET)
	//{
	//	throw std::exception("Error while sending message to client");
	//}

	int res = recv(socket, headers, HEADERS_SIZE, 0);
	if (res == INVALID_SOCKET)
	{
		throw std::exception("Error while recieving from socket");
	}

	
	closesocket(socket);
}


