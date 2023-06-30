#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser user, Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}


void RoomAdminRequestHandler::exitUser()
{
	this->closeRoom(RequestInfo());
	MenuRequestHandler* r = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	r->signout();
	delete r;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == CloseRoom_REQ || info.requestId == StartGame_REQ || info.requestId == GetRoomsStateRoom_REQ)
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

// This function are starting the game and close the current room
RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	if (this->m_room.getAllUsers().size() < 2)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{"Too few players :("}), nullptr};

	}
	Game& game(this->m_handlerFactory.getGameManger().createGame(this->m_room));
	this->m_room.setState(true);
	this->m_roomManager.deleteRoom(this->m_room.getRoomData().id);
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(StartRoomResponse{ 1 }), this->m_handlerFactory.createGameRequestHandler(this->m_user,game)};
}

// This function close the current room
RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	this->m_roomManager.deleteRoom(this->m_room.getRoomData().id);
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(CloseRoomResponse{1}), this->m_handlerFactory.createMenuRequestHandler(this->m_user) };
}

// This function return the room stats
RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	std::vector<int> cardsPerPlayer;
	

	hasGameBegun = this->m_room.isActive();
	players = this->m_room.getAllUsers();

	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetRoomsStateResponse{1,hasGameBegun, players,  }),  nullptr };
}
