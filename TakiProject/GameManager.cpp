#include "GameManager.h"


GameManager& GameManager::getGameManager()
{
	static GameManager manager = GameManager(&MongoDB::getDB());
	return manager;
}

GameManager::GameManager(IDatabase* db) : m_database(&MongoDB::getDB())
{

}

Game& GameManager::createGame(Room& r)
{
    Game new_room(r.getAllUsers());
    this->m_games.push_back(new_room);
    return this->m_games.back();
}

void GameManager::deleteGame(Game& g)
{
	for (int i = 0; i < this->m_games.size(); i++)
	{
		if (this->m_games[i].getPlayers() == g.getPlayers())
		{
			this->m_games.erase(this->m_games.begin() + i);
		}
	}
}

Game& GameManager::getGame(std::string name)
{
	for (int i = 0; i < this->m_games.size(); i++)
	{
		for (int j = 0; j < this->m_games[i].getPlayers().size(); j++)
		{
			if (this->m_games[i].getPlayers()[j] == name)
			{
				return this->m_games[i];
			}
		}
	}
	throw TriviaException(std::string("Room not found"));
}
