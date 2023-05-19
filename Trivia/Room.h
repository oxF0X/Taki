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

}RoomData;


class Room
{
public:
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers() const;

private:
	RoomData m_metatdata;
	std::vector<LoggedUser> m_users;
};