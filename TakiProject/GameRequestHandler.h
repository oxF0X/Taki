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
	GameRequestHandler(LoggedUser m_user, GameManager& m_gameManager, RequestHandlerFactory& m_handlerFactory);

private:
	RequestResult PlayCard(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult getGameSate(RequestInfo info);

	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
	LoggedUser m_user;
	Game& m_game;

};