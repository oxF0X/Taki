#pragma once

#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:

	LoginRequestHandler();
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
};