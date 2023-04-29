#include "JsonRequestPacketDeserializer.h"


void Requests::from_json(const nlohmann::json& j, SignUpRequest& s)
{
	j.at("userName").get_to(s.userName);
	j.at("email").get_to(s.email);
	j.at("password").get_to(s.password);
}

void Requests::from_json(const nlohmann::json& j, LoginRequest& l)
{
	j.at("userName").get_to(l.userName);
	j.at("password").get_to(l.password);
}


Requests::LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<std::uint8_t> l)
{
	return nlohmann::json::parse(l).get<Requests::LoginRequest>();
}

Requests::SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<std::uint8_t> s)
{
	return nlohmann::json::parse(s).get<Requests::SignUpRequest>();
}


