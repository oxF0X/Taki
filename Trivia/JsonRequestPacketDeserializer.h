#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <bitset>
#include "json.hpp"


enum class BYTE : std::uint8_t {};

typedef struct LoginRequest
{
	std::string userName;
	std::string password;
	// Constructor to initialize struct directly from nlohmann::json object
	LoginRequest(const nlohmann::json& j);
} LoginResponse;

typedef struct SignUpRequest
{
	std::string userName;
	std::string password;
	std::string email;
	SignUpRequest(const nlohmann::json& j);
} SignupResponse;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<std::uint8_t> l);
	static SignUpRequest deserializeSignUpRequest(std::vector<std::uint8_t> s);

};