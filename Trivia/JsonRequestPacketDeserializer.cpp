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

	if (!(j.is_object() && j.contains("username") && j.contains("password") && j.contains("email") && j.contains("address") && j.contains("birthday") && j.contains("phoneNumber")))
	{
		throw(ParsingExceprion(std::string("Missing necessary fields")));
	}

	signup.from_json(j, signup);
	return signup;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<std::uint8_t> data)
{
	CreateRoomRequest request;
	nlohmann::json j = nlohmann::json::parse(data);

	if (!(j.is_object() && j.contains("roomName") && j.contains("maxUsers") && j.contains("answerTimeout")))
	{
		throw(ParsingExceprion(std::string("Missing necessary fields")));
	}

	request.from_json(j, request);
	return request;
}

GetPalayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPalayersInRoomRequest(std::vector<std::uint8_t> data)
{
	GetPalayersInRoomRequest request;
	nlohmann::json j = nlohmann::json::parse(data);

	if (!(j.is_object() && j.contains("roomId")))
	{
		throw(ParsingExceprion(std::string("Missing necessary fields")));
	}

	request.from_json(j, request);
	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<std::uint8_t> data)
{
	JoinRoomRequest request;
	nlohmann::json j = nlohmann::json::parse(data);

	if (!(j.is_object() && j.contains("roomId")))
	{
		throw(ParsingExceprion(std::string("Missing necessary fields")));
	}

	request.from_json(j, request);
	return request;
}


