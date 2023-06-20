#include "GameManager.h"

Game GameManager::createGame(Room r)
{
    Game new_room(r.getAllUsers());
    this->m_games.push_back(new_room);
    return new_room;
}

void GameManager::deleteGame(Game g)
{
	for (int i = 0; i < this->m_games.size(); i++)
	{
		if (this->m_games[i].getPlayers() == g.getPlayers())
		{
			this->m_games.erase(this->m_games.begin() + i);
		}
	}
}