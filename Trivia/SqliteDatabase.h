#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include "AuthorizationException.h"
#include <io.h>

#define DB_NAME ".triviaDB.sqlite"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool open() override;
	bool close() override;
	int doesUserExist(std::string username) override;
	int doesPasswordMatch(std::string username, std::string password) override;
	int addNewUser(std::string username, std::string password, std::string email, const std::string address, const std::string phoneNumber, const std::string birthday) override;

private:
	sqlite3* _db;
	static int userCallback(void* ptr, int argc, char** argv, char** azColName);
};