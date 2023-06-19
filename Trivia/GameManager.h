#pragma once

#include "MongoDB.h"
#include "Game.h"
#include "Room.h"


class GameManager
{

public:
	Game createGame(Room r);
	void deleteGame(Game g);
	

private:
	IDatabase* m_database;
	std::vector<Game> m_games;
};

