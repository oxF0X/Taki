#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <bitset>
#include "json.hpp"
#include "Helper.h"
#include "ParsingException.h"



typedef struct LoginRequest
{
	std::string username;
	std::string password;

	LoginRequest() : username(""), password("") {}

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LoginRequest, username, password)
} LoginRequest;


typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
	std::string address;
	std::string birthday;
	std::string phoneNumber;

	SignupRequest() : username(""), password(""), email(""), phoneNumber(), address(), birthday() { }

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SignupRequest, username, password, email, address, birthday, phoneNumber)
} SignupRequest;



class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<std::uint8_t> l);
	static SignupRequest deserializeSignupRequest(std::vector<std::uint8_t> s);

};