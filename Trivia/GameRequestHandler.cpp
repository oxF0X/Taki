#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == LeaveGame_REQ || info.requestId == PlayCard_REQ)
	{
		return true;
	}
	return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	if (info.requestId == LeaveGame_REQ)
	{
		return this->leaveGame(info);

	}
	return this->PlayCard(info);
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	return RequestResult();
}
