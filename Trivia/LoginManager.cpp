#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db) : m_database(db)
{
	this->m_database->open();
}

void LoginManager::signup(const std::string username, const std::string password, const std::string email)
{
	if (this->m_database->addNewUser(username, password, email))
	{
		throw(AuthorizationException(std::string("This user already exists")));
	}

	this->m_loggedUsers.push_back(LoggedUser(username));
}

void LoginManager::login(const std::string username, const std::string password)
{
	if (std::find_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(),
	[&](const LoggedUser& c) { return (c.getUsername() == username); }) != this->m_loggedUsers.end())
	{
		throw(AuthorizationException(std::string("This user already logged in")));
	}

	if (!this->m_database->doesPasswordMatch(username, password))
	{
		throw(AuthorizationException(std::string("Invalid credetionals")));
	}

	this->m_loggedUsers.push_back(LoggedUser(username));
}

void LoginManager::logout(const std::string username)
{
	std::vector<LoggedUser>::iterator it = std::find_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(),
		[&](const LoggedUser& c) { return (c.getUsername() == username); });

	if (it == this->m_loggedUsers.end())
	{
		throw(AuthorizationException(std::string("This user isn't logged in")));
	}

	this->m_loggedUsers.erase(it);
}
