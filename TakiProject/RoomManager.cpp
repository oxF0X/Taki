#include "RoomManager.h"

RoomManager::RoomManager()
{
}

RoomManager& RoomManager::getManager()
{
	static RoomManager manager = RoomManager();
	return manager;
}

void RoomManager::createRoom(const LoggedUser& user, const RoomData& data)
{
	if (data.maxPlayers < 2 || data.maxPlayers > 4)
	{
		throw(TriviaException("The room must cntain atleast 2 palyers"));
	}

	if (this->m_rooms.find(data.id) != this->m_rooms.end())
	{
		throw(TriviaException("This room already exists"));
	}

	{
		std::lock_guard(this->_rooms_mtx);
		this->m_rooms.emplace(data.id, Room(data, user));
	}
}

void RoomManager::deleteRoom(const int& id)
{
	{
		std::lock_guard(this->_rooms_mtx);
		this->m_rooms.erase(id);
	}
}

void RoomManager::addUser(LoggedUser user, int id)
{
	{
		std::lock_guard(this->_rooms_mtx);
		this->getRoom(id).addUser(user);
	}
}

const unsigned int RoomManager::getRoomState(const int& id) const
{
	if (this->m_rooms.find(id) == this->m_rooms.end())
	{
		throw(TriviaException("This room doesn't exsists"));
	}
	return this->m_rooms.at(id).isActive();
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> v;
	for (auto u : this->m_rooms)
	{
		v.push_back(u.second.getRoomData());
	}
	return v;
}

unsigned int RoomManager::getNumbersRooms() const
{
	return unsigned int(this->getRooms().size());
}

Room& RoomManager::getRoom(const int& id)
{
	if (this->m_rooms.find(id) == this->m_rooms.end())
	{
		throw(TriviaException("This room doesn't exsists"));
	}
	return this->m_rooms[id];
}
