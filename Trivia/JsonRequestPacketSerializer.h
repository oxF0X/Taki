#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <bitset>
#include "json.hpp"
#include "Helper.h"
#include "Room.h"

#define LOGIN_RES 100
#define Signup_RES 101
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

typedef struct SignupResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SignupResponse, status)

} SignupResponse;

typedef struct LogoutResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LogoutResponse, status)

} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetRoomsResponse, status, rooms)

} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetPlayersInRoomResponse, players)

} GetPlayersInRoomResponse;

typedef struct GetHightScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetHightScoreResponse, status, statistics)

} GetHightScoreResponse;

typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetPersonalStatsResponse, status, statistics)

} GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JoinRoomResponse, status)

} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreateRoomResponse, status)

} CreateRoomResponse;




class JsonRequestPacketSerializer
{
public:
	static std::vector<std::uint8_t> serializeResponse(ErrorResponse err);
	static std::vector<std::uint8_t> serializeResponse(LoginResponse l);
	static std::vector<std::uint8_t> serializeResponse(SignupResponse s);

	static std::vector<std::uint8_t> serializeResponse(LogoutResponse s);
	static std::vector<std::uint8_t> serializeResponse(GetRoomsResponse s);
	static std::vector<std::uint8_t> serializeResponse(GetPlayersInRoomResponse s);
	static std::vector<std::uint8_t> serializeResponse(GetHightScoreResponse s);
	static std::vector<std::uint8_t> serializeResponse(GetPersonalStatsResponse s);
	static std::vector<std::uint8_t> serializeResponse(JoinRoomResponse s);
	static std::vector<std::uint8_t> serializeResponse(CreateRoomResponse s);

private:
	static std::vector<uint8_t> buildMsg(nlohmann::json j, unsigned int id);

}; 
