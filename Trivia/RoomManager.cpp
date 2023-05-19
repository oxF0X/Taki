#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser& user, const RoomData& data)
{
	if (this->m_rooms.find(data.id) != this->m_rooms.end())
	{
		throw(std::runtime_error("This room already exists"));
	}

	this->m_rooms[data.id] = Room(data, user);
}

void RoomManager::deleteRoom(const int& id)
{
	this->m_rooms.erase(id);
}

const unsigned int RoomManager::getRoomState(const int& id) const
{
	if (this->m_rooms.find(id) == this->m_rooms.end())
	{
		throw(std::runtime_error("This room doesn't exsists"));
	}
	return this->m_rooms.at(id).isActive();
}
