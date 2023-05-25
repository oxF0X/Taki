#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory): m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{

}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == Signout_REQ || info.requestId == GetRooms_REQ || info.requestId == getPlayers_REQ || info.requestId == JoinRoom_REQ || info.requestId == CreateRoom_REQ)
	{
		return true;
	}
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
	case Signout_REQ:
		return this->signout(info);
	case GetRooms_REQ:
		return this->getRooms(info);
	case getPlayers_REQ:
		return this->getPlayersInRoom(info);
	case JoinRoom_REQ:
		return this->joinRoom(info);
	case CreateRoom_REQ:
		return this->createRoom(info);
	}
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	this->m_handlerFactory.getLoginManger().logout(this->m_user.getUsername());
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(SignupResponse{1}), nullptr };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	std::vector<RoomData> rooms;
	rooms = this->m_roomManager.getRooms();
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse{1, rooms}), nullptr };
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	GetPalayersInRoomRequest room;
	std::vector<std::string> players;
	try
	{
		room = JsonRequestPacketDeserializer::deserializeGetPalayersInRoomRequest(info.buffer);
		players = this->m_roomManager.getRoom(room.roomId).getAllUsers();

	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	catch (AuthorizationException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse{players}), nullptr };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomRequest room;
	try
	{
		room = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
		this->m_roomManager.getRoom(room.roomId).addUser(this->m_user);

	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	catch (AuthorizationException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse{1}), nullptr };
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	CreateRoomRequest room;
	try
	{
		room = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
		this->m_roomManager.createRoom(this->m_user, RoomData{this->m_roomManager.getNumbersRooms(), room.maxId, room.cardsCount, room.turnTime, false, room.roomName });
		
	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	catch (AuthorizationException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse{1}), nullptr };
}

