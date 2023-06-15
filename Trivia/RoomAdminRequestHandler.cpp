#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser user, Room room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == CloseRoom_REQ || info.requestId == StartGame_REQ	|| info.requestId == GetRoomsStateRoom_REQ)
	{
		return true;
	}
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
	case CloseRoom_REQ:
		return this->closeRoom(info);
	case StartGame_REQ:
		return this->startGame(info);
	case GetRoomsStateRoom_REQ:
		return this->getRoomState(info);
	}
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{

	return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	std::vector<int> cardsPerPlayer;
	std::vector<std::string> LastPlayForEachPlayer;

	hasGameBegun = this->m_room.isActive();
	players = this->m_room.getAllUsers();

	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetRoomsStateResponse{1,hasGameBegun, players,  }), nullptr };
}
