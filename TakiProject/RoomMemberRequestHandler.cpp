#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser user, Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

void RoomMemberRequestHandler::exitUser()
{
	this->leaveRoom(RequestInfo());
	MenuRequestHandler* r = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	r->signout();
	delete r;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == LeaveRoom_REQ || info.requestId == GetRoomsStateRoom_REQ)
	{
		return true;
	}
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
	case LeaveRoom_REQ:
		return this->leaveRoom(info);
	case GetRoomsStateRoom_REQ:
		return this->getRoomState(info);
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	this->m_room.removeUser(this->m_user);
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LeaveRoomResponse{1}), this->m_handlerFactory.createMenuRequestHandler(this->m_user) };
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	std::vector<int> cardsPerPlayer;
	std::vector<std::string> LastPlayForEachPlayer;



	hasGameBegun = this->m_room.isActive();
	players = this->m_room.getAllUsers();

	std::string str = "";
	for (std::string s : players)
	{
		str += s;
	}
	std::cout << this->m_user.getUsername() << " " << str << std::endl;
	if (!hasGameBegun)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetRoomsStateResponse{1,hasGameBegun, players }), nullptr };
	}
	Game& game(this->m_handlerFactory.getGameManger().getGame(this->m_user.getUsername()));

	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(StartRoomResponse{ 1 }), this->m_handlerFactory.createGameRequestHandler(this->m_user,game)};
}
