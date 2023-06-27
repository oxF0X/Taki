#pragma once
#include "MongoDB.h"
#include <vector>
#include <iostream>

class StatisticsManager
{
public:
	StatisticsManager();
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStats(std::string username);

private:
	IDatabase* m_database;
};

