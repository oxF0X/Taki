#include "JsonRequestPacketDeserializer.h"



LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<std::uint8_t> l)
{
	LoginRequest login = { "sad", "sda" };
	nlohmann::json j;
	login.from_json(j, login);
	return login;
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<std::uint8_t> s)
{
	SignUpRequest login = { "sad", "sda" };
	nlohmann::json j;
	login.from_json(j, login);
	return login;
}


