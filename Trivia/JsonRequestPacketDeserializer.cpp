#include "JsonRequestPacketDeserializer.h"

LoginRequest::LoginRequest(const nlohmann::json& j)
{
	userName = j["username"].get<std::string>();
	password = j["password"].get<std::string>();
}

SignUpRequest::SignUpRequest(const nlohmann::json& j)
{
	userName = j["username"].get<std::string>();
	password = j["password"].get<std::string>();
	email = j["email"].get<std::string>();
}


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<std::uint8_t> l)
{
	return nlohmann::json::from_bson<LoginRequest>(nlohmann::json::from_bson(l));

}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<std::uint8_t> s)
{
	return nlohmann::json::from_bson<SignUpRequest>(nlohmann::json::from_bson(s));
}

