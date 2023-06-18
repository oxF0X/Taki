#include "GameManager.h"

Game GameManager::createGame(Room r)
{
    Game new_room(r.getAllUsers());
    this->m_games.push_back(new_room);
    return new_room;
}
