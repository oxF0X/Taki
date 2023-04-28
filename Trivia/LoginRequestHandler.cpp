#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == LOGIN_REQ || info.requestId == SIGNUP_REQ)
	{
		return true;
	}
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{

	return RequestResult{ info.buffer, nullptr};
}
