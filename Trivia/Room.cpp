#include "Room.h"

Room::Room(RoomData data, LoggedUser owner) : m_metatdata(data)
{
	this->m_users.push_back(owner);
}

Room::Room()
{

}

void Room::addUser(LoggedUser user)
{
	if (std::find_if(this->m_users.begin(), this->m_users.end(),
		[&](const LoggedUser& c) { return (c.getUsername() == user.getUsername()); }) != this->m_users.end())
	{
		throw(std::runtime_error(std::string("This user already in the room")));
	}
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	this->m_users.erase(std::remove_if(m_users.begin(), m_users.end(),
		[&](LoggedUser u) { return u.getUsername() == user.getUsername(); }));
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> v;
	for (LoggedUser u : this->m_users)
	{
		v.push_back(u.getUsername());
	}
	return v;
}

RoomData Room::getRoomData() const
{
	return this->m_metatdata;
}

const unsigned int Room::isActive() const
{
	return this->m_metatdata.isActive;
}
