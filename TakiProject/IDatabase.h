#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <mutex>  
#include <shared_mutex>


class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(std::string username) = 0;
	virtual int doesPasswordMatch(std::string username, std::string password) = 0;
	virtual int addNewUser(std::string username, std::string password, std::string email, const std::string address, const std::string phoneNumber, const std::string birthday) = 0;
	virtual void writeResultToDB(std::vector<std::string> players, std::string winner) = 0;
	virtual std::vector<std::string> getUsers() = 0;
	// statistics
	virtual int getNumOfWins(std::string username) = 0;
	virtual int getNumsOfPlayerGames(std::string username) = 0;
};