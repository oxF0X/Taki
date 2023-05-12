#pragma once

#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketSerializer.h"
#include "RequestHandlerFactory.h"

#define PORT 4444
#define CODE_SIZE 1
#define LENGTH_SIZE 4

class Comunicator
{
public:

	~Comunicator();
	void startHandleRequests();
	static Comunicator getComunicator(RequestHandlerFactory& handler);
private:
	void bindAndListen();
	void handleNewClient(SOCKET socket);

	///////////////////////////////

	void acceptClient();
	Comunicator(RequestHandlerFactory& handler);
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	static bool is_exsit;
};