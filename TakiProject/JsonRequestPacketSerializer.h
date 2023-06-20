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
#define SIGNOUT_RES 111
#define GET_ROOMS_RES 103
#define GET_PLAYERS_RES 104
#define JOIN_ROOM_RES 105
#define CREATE_ROOM_RES 106
#define CLOSE_ROOM_RES 107
#define START_ROOM_RES 108
#define LEAVE_ROOM_RES 109
#define GET_ROOM_STATE_RES 110
#define GetGameStateRoom_RES 111

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

typedef struct CloseRoomResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CloseRoomResponse, status)

} CloseRoomResponse;

typedef struct StartRoomResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StartRoomResponse, status)

} StartRoomResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LeaveRoomResponse, status)

} LeaveRoomResponse;

typedef struct GetRoomsStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	std::vector<int> cardsPerPlayer;
	std::vector<std::string> LastPlayForEachPlayer;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetRoomsStateResponse, status, hasGameBegun, players, cardsPerPlayer, LastPlayForEachPlayer)

} GetRoomsStateResponse;


typedef struct LeaveGameResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LeaveGameResponse, status)
} LeaveGameResponse;

typedef struct DrawCardFromDeckResponse
{
	unsigned int status;
	std::string card;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DrawCardFromDeckResponse, status, card)

} DrawCardFromDeckResponse;

typedef struct PlaceCardResponse
{
	unsigned int status;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlaceCardResponse, status)

} PlaceCardResponse;

typedef struct PlayerResults
{
	std::string username;
	int cardsInHand;
	float averagePlayTime;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayerResults, username, cardsInHand, averagePlayTime)

} PlayerResults;

typedef struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetGameResultsResponse, status, results)

} GetGameResultsResponse;

typedef struct GetGameStateResponse
{
	unsigned int status;
	bool hasGameEnd;
	std::vector<std::string> players;
	std::vector<int> cardsPerPlayer;
	std::vector<std::string> cards;
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetGameStateResponse, status, hasGameEnd, players, cardsPerPlayer, cards)

} GetGameStateResponse;

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

	static std::vector<std::uint8_t> serializeResponse(CloseRoomResponse s);
	static std::vector<std::uint8_t> serializeResponse(StartRoomResponse s);
	static std::vector<std::uint8_t> serializeResponse(LeaveRoomResponse s);
	static std::vector<std::uint8_t> serializeResponse(GetRoomsStateResponse s);

	static std::vector<std::uint8_t> serializeResponse(GetGameResultsResponse s);
	static std::vector<std::uint8_t> serializeResponse(DrawCardFromDeckResponse s);
	static std::vector<std::uint8_t> serializeResponse(PlaceCardResponse s);
	static std::vector<std::uint8_t> serializeResponse(LeaveGameResponse s);
	static std::vector<std::uint8_t> serializeResponse(GetGameStateResponse s);

private:
	static std::vector<uint8_t> buildMsg(nlohmann::json j, unsigned int id);

}; 
