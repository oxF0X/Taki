#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "json.hpp"
#include "TriviaException.h"

typedef struct RoomData
{
	unsigned int id;
	unsigned int maxPlayers;
	unsigned int timePerPlay;
	unsigned int isActive;
	std::string name;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(RoomData, id, maxPlayers, timePerPlay, isActive, name)
}RoomData;


class Room
{
public:
	Room(RoomData data, LoggedUser owner);
	Room();
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers() const;
	RoomData getRoomData() const;
	const unsigned int isActive() const;
	const void setState(const bool state);

private:
	RoomData m_metatdata;
	std::vector<LoggedUser> m_users;
};