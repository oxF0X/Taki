#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <bitset>
#include "json.hpp"


namespace Requests
{
	typedef struct LoginRequest
	{
		std::string userName;
		std::string password;
	} LoginResponse;

	typedef struct SignUpRequest
	{
		std::string userName;
		std::string password;
		std::string email;
	} SignupResponse;

	void from_json(const nlohmann::json& j, SignUpRequest& s);
	void from_json(const nlohmann::json& j, LoginRequest& l);
}

class JsonRequestPacketDeserializer
{
public:
	static Requests::LoginRequest deserializeLoginRequest(std::vector<std::uint8_t> l);
	static Requests::SignUpRequest deserializeSignUpRequest(std::vector<std::uint8_t> s);

};