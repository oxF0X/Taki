#include "LoginRequestHandler.h"



LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handler):m_handlerFactory(handler)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == LOGIN_REQ || info.requestId == Signup_REQ)
	{
		return true;
	}
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	if (info.requestId == LOGIN_REQ)
	{
		LoginRequest l;
		try
		{
			l = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
		}
		catch (ParsingExceprion& e)
		{
			return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr};
		}

		std::cout << "[Login] " << l.username << " " << l.password << std::endl;
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LoginResponse{1}), nullptr };

	}

	SignupRequest s;
	try
	{
		s = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}

	std::cout << "[Signup] " << s.username << " " << s.password << " " << s.email << std::endl;
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LoginResponse{1}), nullptr };
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
	if (this->isRequestRelevant(info))
	{
		return this->handleRequest(info);
	}
	return RequestResult{ info.buffer,  nullptr };

}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
	if (this->isRequestRelevant(info))
	{
		return this->handleRequest(info);
	}
	return RequestResult{ info.buffer,  nullptr };

}
