#include "LoginManager.h"


LoginManager::LoginManager(IDatabase* db) : m_database(db)
{
	this->m_database->open();
}

LoginManager& LoginManager::getLoginManager(IDatabase* db)
{
	static LoginManager m(db);
	return m;
}

void LoginManager::signup(const std::string username, const std::string password, const std::string email, const std::string address, const std::string phoneNumber, const std::string birthday)
{
	this->matchRegex(std::regex("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-]+)(\\.[a-zA-Z]{2,5}){1,2}$"), email, "Invalid email");
    
	this->matchRegex(std::regex("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*\\W).{8}$"), password, "Invalid password");

	this->matchRegex(std::regex("^[a-zA-Z\\s]+,\\s*\\d+,\\s*[A-Za-z\\s]+$"), address, "Invalid address");

	this->matchRegex(std::regex("0\\d{2}-\\d{4}-\\d{3}$|0\\d{1}-\\d{4}\\d{3}$"), phoneNumber, "Invalid phone number");
	this->matchRegex(std::regex("\\d{2}.\\d{2}.\\d{4}$|\\d{2}/\\d{3}/\\d{4}$"), birthday, "Invalid birthday");

	
	if (this->m_database->addNewUser(username, password, email, address, phoneNumber, birthday))
	{
		throw(TriviaException(std::string("This user already exists")));
	}

	this->m_loggedUsers.push_back(LoggedUser(username));
}

void LoginManager::login(const std::string username, const std::string password)
{
	if (std::find_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(),
	[&](const LoggedUser& c) { return (c.getUsername() == username); }) != this->m_loggedUsers.end())
	{
		throw(TriviaException(std::string("This user already logged in")));
	}

	if (!(this->m_database->doesPasswordMatch(username, password)))
	{
		throw(TriviaException(std::string("Invalid credetionals")));
	}

	this->m_loggedUsers.push_back(LoggedUser(username));
}

void LoginManager::logout(const std::string username)
{
	std::vector<LoggedUser>::iterator it = std::find_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(),
		[&](const LoggedUser& c) { return (c.getUsername() == username); });

	if (it == this->m_loggedUsers.end())
	{
		throw(TriviaException(std::string("This user isn't logged in")));
	}

	this->m_loggedUsers.erase(it);
}

LoginManager::~LoginManager()
{
}

void LoginManager::matchRegex(std::regex r, std::string s, std::string err)
{
	if (!std::regex_search(s, r))
	{
		throw(TriviaException(std::string(err)));
	}

}
