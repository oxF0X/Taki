#pragma once

#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "MongoDB.h"
#include <mutex>

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	RequestResult signout();
	void exitUser() override;



private:
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);


	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
	IDatabase* m_database;

};