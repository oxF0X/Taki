#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;


// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(const SOCKET sc, const int bytesNum)
{
	
	 const char* data = getPartFromSocket(sc, bytesNum).c_str();
	 return *(reinterpret_cast<const int*>(data));
}

std::vector<uint8_t> Helper::getDataFromSocket(SOCKET sc, const int bytesNum)
{
	if (bytesNum == 0)
	{
		return std::vector<uint8_t>();
	}
	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::vector<uint8_t> byte_vector(data, data + strlen(data));
	delete[] data;
	return byte_vector;
	
}





// send data to socket
void Helper::sendData(const SOCKET sc, std::vector<uint8_t> message)
{
	char* data= new char[message.size() + 1];
	std::memcpy(data, message.data(), message.size());
	data[message.size()] = '\0';

	if (send(sc, data, message .size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::vector<uint8_t> Helper::intToBytes(int value)
{
	std::vector<uint8_t> bytes(sizeof(int));
	std::memcpy(bytes.data(), &value, sizeof(int));
	return bytes;
}

std::string Helper::getPartFromSocket(const SOCKET sc, const int bytesNum)
{
	if (bytesNum == 0)
	{
		return "";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::string received(data);
	delete[] data;
	return received;
}
