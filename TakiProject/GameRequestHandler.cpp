#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == LeaveGame_REQ || info.requestId == PlayCard_REQ || info.requestId  == DrawCard_REQ || info.requestId == GetGameState_REQ || info.requestId == GetGameResult_REQ)
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
		this->m_game.playCard(this->m_user, Card("00"));
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(DrawCardFromDeckResponse{1, }), nullptr };
	case GetGameState_REQ:
		return this->getGameSate(info);
		break;
	case GetGameResult_REQ:
		return this->getGameResults(info);
		break;
	}
}

GameRequestHandler::GameRequestHandler(LoggedUser user, Game& game): m_user(user), m_game(game), m_gameManager(GameManager::getGameManager()), m_handlerFactory(RequestHandlerFactory::getFactory(&MongoDB::getDB()))
{
}

void GameRequestHandler::exitUser()
{
	this->m_game.removePlayer(this->m_user);
	MenuRequestHandler* r = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	r->signout();
	delete r;

}

// This function activates the function play card in the game
RequestResult GameRequestHandler::PlayCard(RequestInfo info)
{
	PlaceCardRequest card;
	try
	{
	card = JsonRequestPacketDeserializer::deserializePlaceCardRequest(info.buffer);
	this->m_game.playCard(this->m_user, Card(card.cardId));
	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(PlaceCardResponse{1}), nullptr};
}

// This function activates the remove player from the game
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

// This function gets the game result from the game class
RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	std::map<std::string, std::vector<std::string>> cards = this->m_game.getCardsByPlayer();

	if (!this->m_game.IsProgress())
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetGameResultsResponse{ this->m_game.getWinner()}), this->m_handlerFactory.createMenuRequestHandler(LoggedUser{this->m_user.getUsername()}) };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetGameResultsResponse{""}), nullptr };

}

// This function return the game stats
RequestResult GameRequestHandler::getGameSate(RequestInfo info)
{
	bool isProgress;
	std::vector<std::string> players;
	std::vector<int> cardsPerPlayer;
	std::map<std::string, std::vector<std::string>> cards;

	isProgress = this->m_game.IsProgress();
	players = this->m_game.getPlayers();
	cards = this->m_game.getCardsByPlayer();
	for (auto it: cards)
	{
		if (it.first != this->m_user.getUsername())
		{
			cardsPerPlayer.push_back(it.second.size());
		}
	}
	while (cardsPerPlayer.size() < 4)
	{
		cardsPerPlayer.push_back(0);
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(GetGameStateResponse{1,isProgress, players, cardsPerPlayer, cards[this->m_user.getUsername()], this->m_game.getCurrentCard().getCode(), this->m_game.getCurrentPlayer()}), nullptr};
}


