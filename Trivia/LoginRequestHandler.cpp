#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
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
		LoginRequest l = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
		std::cout << "[Login] " << l.username << " " << l.password << std::endl;
		return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LoginResponse{1}), nullptr };

	}

	SignupRequest s = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
	std::cout << "[Login] " << s.username << " " << s.password << " " << s.email << std::endl;
	return RequestResult{ JsonRequestPacketSerializer::serializeResponse(LoginResponse{1}), nullptr };
}
