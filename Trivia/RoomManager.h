#pragma once

#include "Room.h"
#include <map>

class RoomManager
{
public:
	void createRoom(const LoggedUser& user, const RoomData& data);
	void deleteRoom(const int& id);
	const unsigned int getRoomState(const int& id) const;
	std::vector<RoomData> getRooms() const;
	const Room& getRoom(const int& id);

private:
	std::map<int, Room> m_rooms;
};