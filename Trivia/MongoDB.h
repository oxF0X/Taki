#pragma once

#pragma comment (lib, "C:\\mongo-cxx-driver\\lib\\bsoncxx.lib")
#pragma comment (lib, "C:\\mongo-cxx-driver\\lib\\mongocxx.lib")


#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/operation_exception.hpp>

#include <WinSock2.h>
#include <Windows.h>

#include "IDatabase.h"
#include "TriviaException.h"
#include <algorithm>

#define DB_NAME "Trivia"
#define USERS_COLLECTION "users"

class MongoDB : public IDatabase
{
public:
	~MongoDB();
	bool open() override;
	bool close() override;
	int doesUserExist(std::string username) override;
	int doesPasswordMatch(std::string username, std::string password) override;
	int addNewUser(std::string username, std::string password, std::string email, const std::string address, const std::string phoneNumber, const std::string birthday) override;
	static MongoDB& getDB();

private:
	mongocxx::client _client;
	MongoDB();
};