#pragma once

#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <map>
#include <string>

#include "LoginRequestHandler.h"

#define PORT 4444

class Comunicator
{
public:
	Comunicator();
	~Comunicator();
	void startHandleRequests();

private:
	void bindAndListen();
	void handleNewClient(SOCKET socket);

	///////////////////////////////

	void acceptClient();

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler> m_clients;
};