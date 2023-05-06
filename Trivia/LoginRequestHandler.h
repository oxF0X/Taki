#pragma once

#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include  "JsonRequestPacketSerializer.h"

class LoginRequestHandler : public IRequestHandler
{
public:

	LoginRequestHandler();
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
};