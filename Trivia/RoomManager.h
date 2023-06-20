#pragma once

#include "Room.h"
#include "TriviaException.h"
#include <map>
#include <mutex>

class RoomManager
{
public:
	static RoomManager& getManager();
	void createRoom(const LoggedUser& user, const RoomData& data);
	void deleteRoom(const int& id);
	const unsigned int getRoomState(const int& id) const;
	std::vector<RoomData> getRooms() const;
	unsigned int getNumbersRooms() const;
	Room& getRoom(const int& id);

private:
	RoomManager();
	std::mutex _rooms_mtx;
	std::map<int, Room> m_rooms;
};