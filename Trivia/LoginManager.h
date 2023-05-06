#pragma once

#include "SqliteDatabase.h"
#include <vector>
#include "LoggedUser.h"
#include "AuthorizationException.h"
#include <algorithm>


class LoginManager
{
public:
	LoginManager(IDatabase* db);
	void signup(const std::string username, const std::string password, const std::string email);
	void login(const std::string username, const std::string password);
	void logout(const std::string username);

private:
	IDatabase *m_database;
	std::vector<LoggedUser> m_loggedUsers;
};