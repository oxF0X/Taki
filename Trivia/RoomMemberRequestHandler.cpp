#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser user, Room room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_user(user),m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	if ( info.requestId == LeaveRoom_REQ || info.requestId == GetRoomsStateRoom_REQ )
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
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LeaveRoomResponse{1}), nullptr };
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
	CreateRoomRequest room;
	try
	{
		room = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
		this->m_room;

	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse{1}), nullptr };
}
