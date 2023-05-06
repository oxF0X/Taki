#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include  "JsonRequestPacketSerializer.h"

class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;


public:

	LoginRequestHandler(RequestHandlerFactory& handler);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);


};