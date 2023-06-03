#pragma once


#include "RequestHandlerFactory.h"
#include "TriviaException.h"
#include "JsonRequestPacketDeserializer.h"
#include  "JsonRequestPacketSerializer.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;



class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);

public:

	LoginRequestHandler(RequestHandlerFactory& handler);
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
};