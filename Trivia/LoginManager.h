#pragma once

#include "SqliteDatabase.h"
#include <vector>
#include "LoggedUser.h"
#include "AuthorizationException.h"
#include <algorithm>
#include <regex>


class LoginManager
{
public:
	LoginManager(IDatabase* db);
	void signup(const std::string username, const std::string password, const std::string email, const std::string address, const std::string phoneNumber, const std::string birthday);
	void login(const std::string username, const std::string password);
	void logout(const std::string username);

private:
	IDatabase *m_database;
	std::vector<LoggedUser> m_loggedUsers;
};