#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == LeaveGame_REQ || info.requestId == PlayCard_REQ || info.requestId  == DrawCard_REQ)
	{
		return true;
	}
	return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{

	switch (info.requestId)
	{
	case LeaveGame_REQ:
		return this->leaveGame(info);
		break;
	case PlayCard_REQ:
		return this->PlayCard(info);
		break;
	case DrawCard_REQ:
		//this->m_game.playCard
	}
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	try
	{
		this->m_game.removePlayer(this->m_user);
	}
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{JsonRequestPacketSerializer::serializeResponse(LeaveGameResponse{ 1 }), this->m_handlerFactory.createMenuRequestHandler(LoggedUser{this->m_user.getUsername()})};
}

RequestResult GameRequestHandler::getGameSate(RequestInfo info)
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
