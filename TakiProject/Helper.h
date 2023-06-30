#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>



class Helper
{
public:
	static int getIntPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::vector<uint8_t> getDataFromSocket(SOCKET sc, const int bytesNum);
	static void sendData(const SOCKET sc, const std::vector<uint8_t> message);
	static std::vector<uint8_t> intToBytes(int value);

private:
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum);

};


