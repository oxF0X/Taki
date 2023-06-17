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
	this->m_roomManager.deleteRoom(this->m_room.getRoomData().id);
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(CloseRoomResponse{1}), new MenuRequestHandler(this->m_user, this->m_roomManager, this->m_handlerFactory)};
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

	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetRoomsStateResponse{1,hasGameBegun, players,  }),  new RoomAdminRequestHandler(this->m_user, this->m_roomManager.getRoom(this->m_roomManager.getNumbersRooms() - 1), this->m_roomManager, this->m_handlerFactory) };
}
