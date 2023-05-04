#include "JsonRequestPacketDeserializer.h"



LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<std::uint8_t> l)
{
	LoginRequest login;
	nlohmann::json j = nlohmann::json::parse(l);
	login.from_json(j, login);
	return login;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<std::uint8_t> s)
{
	SignupRequest Signup;
	nlohmann::json j = nlohmann::json::parse(s);
	Signup.from_json(j, Signup);
	return Signup;
}


