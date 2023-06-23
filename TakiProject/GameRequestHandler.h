#pragma once
#include "LoggedUser.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"



class RequestHandlerFactory;

class GameRequestHandler: public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	GameRequestHandler(LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory, Game& game);
	void exitUser() override;
private:
	RequestResult PlayCard(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult getGameSate(RequestInfo info);

	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
	Game& m_game;

};