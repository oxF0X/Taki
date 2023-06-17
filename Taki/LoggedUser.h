#pragma once

#include <iostream>
#include <string>

class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername() const;

private:
	std::string m_username;
};