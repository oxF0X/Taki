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
