#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <bitset>
#include "json.hpp"
#include "Helper.h"

#define LOGIN_RES 100
#define SIGNUP_RES 101
#define ERROR_RES 102

typedef struct ErrorResponse
{
	std::string message;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ErrorResponse, message)

} ErrorResponse;

typedef struct LoginResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LoginResponse, status)

} LoginResponse;

typedef struct SignUpResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SignUpResponse, status)

} SignupResponse;

class JsonRequestPacketSerializer
{
public:
	static std::vector<std::uint8_t> serializeResponse(ErrorResponse err);
	static std::vector<std::uint8_t> serializeResponse(LoginResponse l);
	static std::vector<std::uint8_t> serializeResponse(SignUpResponse s);

private:
	static std::vector<uint8_t> buildMsg(nlohmann::json j, unsigned int id);
}; 
