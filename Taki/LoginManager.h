#pragma once

#include "MongoDB.h"
#include <vector>
#include "LoggedUser.h"
#include "TakiException.h"
#include <algorithm>
#include <regex>


class LoginManager
{
public:
	static LoginManager& getLoginManager(IDatabase* db);
	void signup(const std::string username, const std::string password, const std::string email, const std::string address, const std::string phoneNumber, const std::string birthday);
	void login(const std::string username, const std::string password);
	void logout(const std::string username);
	~LoginManager();
private:
	IDatabase *m_database;
	std::vector<LoggedUser> m_loggedUsers;

	LoginManager(IDatabase* db);
	void matchRegex(std::regex r, std::string s, std::string err);
};