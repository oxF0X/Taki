#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "json.hpp"

enum class BYTE : std::uint8_t {};

typedef struct ErrorResponse
{
	std::string message;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ErrorResponse, message)
} ErrorResponse;

typedef struct LoginResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginResponse, status)
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SignupResponse, status)
} SignupResponse;

class JsonRequestPacketDeserializer
{
	static std::vector<std::uint8_t> serializeResponse(ErrorResponse err);
	static std::vector<std::uint8_t> serializeResponse(LoginResponse l);
	static std::vector<std::uint8_t> serializeResponse(SignupResponse s);
};