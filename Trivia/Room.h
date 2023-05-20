#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "LoggedUser.h"

typedef struct RoomData
{
	unsigned int id;
	unsigned int maxPlayers;
	unsigned int numOfCards;
	unsigned int timePerMove;
	unsigned int isActive;
	std::string name;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(RoomData, id, maxPlayers, numOfCards, timePerMove, isActive, name)
}RoomData;


class Room
{
public:
	Room(RoomData data, LoggedUser owner);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers() const;
	const unsigned int isActive() const;

private:
	RoomData m_metatdata;
	std::vector<LoggedUser> m_users;
};