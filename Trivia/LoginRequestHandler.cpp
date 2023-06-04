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
		return this->login(info);

	}
	return this->signup(info);
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
	LoginRequest l;
	
	try
	{
		l = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
		this->m_handlerFactory.getLoginManger().login(l.username, l.password);
	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LoginResponse{1}), this->m_handlerFactory.createMenuRequestHandler(LoggedUser{l.username}) };
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
	SignupRequest s;
	try
	{
		s = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);

		this->m_handlerFactory.getLoginManger().signup(s.username, s.password, s.email, s.address, s.phoneNumber, s.birthday);
	}
	catch (ParsingExceprion& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	catch (TriviaException& e)
	{
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(ErrorResponse{std::string(e.what())}), nullptr };
	}
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(SignupResponse{1}), 
		this->m_handlerFactory.createMenuRequestHandler(LoggedUser{s.username})};
}
