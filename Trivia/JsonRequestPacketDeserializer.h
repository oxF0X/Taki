#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <bitset>
#include "json.hpp"
#include "Helper.h"



typedef struct LoginRequest
{
	std::string userName;
	std::string password;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LoginRequest, userName, password)
} LoginRequest;

typedef struct SignUpRequest
{
	std::string userName;
	std::string password;
	std::string email;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SignUpRequest, userName, password, email)
} SignUpRequest;



class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<std::uint8_t> l);
	static SignUpRequest deserializeSignUpRequest(std::vector<std::uint8_t> s);

};