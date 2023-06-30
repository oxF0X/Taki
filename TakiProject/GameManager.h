#pragma once

#include "MongoDB.h"
#include "Game.h"
#include "Room.h"


class GameManager
{

public:
	static GameManager& getGameManager();
	Game& createGame(Room& r);
	void deleteGame(Game& g);
	Game& getGame(std::string name);

private:
	
	GameManager(IDatabase* db);
	IDatabase* m_database;
	std::vector<Game> m_games;
};

