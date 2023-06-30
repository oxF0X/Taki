#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory), m_database(&MongoDB::getDB())
{

}

void MenuRequestHandler::exitUser()
{
	this->signout();
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == Signout_REQ || info.requestId == GetRooms_REQ || info.requestId == getPlayers_REQ || info.requestId == JoinRoom_REQ || info.requestId == CreateRoom_REQ|| info.requestId == GetNumOfGames_REQ || info.requestId == GetNumOfWins_REQ)
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
		return this->signout();
	case GetRooms_REQ:
		return this->getRooms(info);
	case getPlayers_REQ:
		return this->getPlayersInRoom(info);
	case JoinRoom_REQ:
		return this->joinRoom(info);
	case CreateRoom_REQ:
		return this->createRoom(info);
	case GetNumOfGames_REQ:
		return this->getPersonalStats(info);
	case GetNumOfWins_REQ:
		return this->getHighScore(info);
	}
}

RequestResult MenuRequestHandler::signout()
{
	this->m_handlerFactory.getLoginManger().logout(this->m_user.getUsername());
	std::cout << "User disconected " << this->m_user.getUsername() << std::endl;

	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LogoutResponse{1}), this->m_handlerFactory.createLoginRequestHandler() };
}

// This function returns all the rooms that are available
RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	std::vector<RoomData> rooms;
	rooms = this->m_roomManager.getRooms();
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse{1, rooms}), nullptr };
}

// This function returns all the players in the room
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
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}),  nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse{players}), nullptr };
}

// This function connect user to room
RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomRequest room;
	try
	{
		room = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
		this->m_roomManager.addUser(this->m_user, room.roomId);

	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}),  nullptr };
	}
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse{1}), this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_roomManager.getRoom(room.roomId)) };
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	CreateRoomRequest room;
	try
	{
		room = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
		this->m_roomManager.createRoom(this->m_user, RoomData{this->m_roomManager.getNumbersRooms(), room.maxUsers, room.answerTimeout, false, room.roomName });

	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}),  nullptr };
	}
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse{1}),  this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_roomManager.getRoom(this->m_roomManager.getNumbersRooms() - 1)) };
}

// This function returns all the stats of the user
RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{

	std::vector<std::string> stats;
	stats = this->m_handlerFactory.getStatisticsManager().getUserStats(this->m_user.getUsername());
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetPersonalStatsResponse{1, stats}), nullptr };
	
}

// This function returns all the stats of the best user
RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	std::vector<std::string> users = this->m_database->getUsers();
	std::vector<std::string> stats;
	std::string winner;
	std::string numOfWins = "0";
	for (int i = 0; i < users.size(); i++)
	{
		stats = this->m_handlerFactory.getStatisticsManager().getUserStats(users[i]);
		if (numOfWins < stats[2])
		{
			winner = stats[0];
			numOfWins = stats[2];
		}
	}
	stats.clear();
	stats.push_back(winner);
	stats.push_back(numOfWins);
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetHightScoreResponse{1, stats}), nullptr };
}

