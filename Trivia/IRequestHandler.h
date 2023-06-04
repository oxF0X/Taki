#pragma once

#include <vector>
#include <string>
#include <iostream>

#define LOGIN_REQ 10
#define Signup_REQ 11
#define Signout_REQ 12
#define GetRooms_REQ 13
#define getPlayers_REQ 14
#define JoinRoom_REQ 15
#define CreateRoom_REQ 16
#define CloseRoom_REQ 17
#define StartGame_REQ 18
#define LeaveRoom_REQ 19
#define GetRoomsStateRoom_REQ 20


class IRequestHandler;

typedef struct RequestInfo
{
	int requestId;
	std::vector<uint8_t> buffer;
} RequestInfo;

typedef struct RequestResult
{
	std::vector<uint8_t> buffer;
	IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};

