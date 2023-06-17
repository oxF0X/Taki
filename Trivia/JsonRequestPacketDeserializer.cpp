#include "JsonRequestPacketDeserializer.h"



LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<std::uint8_t> l)
{
	LoginRequest login;
	nlohmann::json j = nlohmann::json::parse(l);

	if (!(j.is_object() && j.contains("username") && j.contains("password")))
	{
		throw(ParsingExceprion(std::string("Missing necessary fields")));
	}
	login.from_json(j, login);
	return login;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<std::uint8_t> s)
{
	SignupRequest signup;
	nlohmann::json j = nlohmann::json::parse(s);

	if (!(j.is_object() && j.contains("username") && j.contains("password") && j.contains("email")))
	{
		throw(ParsingExceprion(std::string("Missing necessary fields")));
	}

	signup.from_json(j, signup);
	return signup;
}


