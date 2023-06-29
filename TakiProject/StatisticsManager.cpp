#include "StatisticsManager.h"

StatisticsManager::StatisticsManager() :m_database(&MongoDB::getDB())
{
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	return std::vector<std::string>();
}

std::vector<std::string> StatisticsManager::getUserStats(std::string username)
{
	std::vector<std::string> result;
	int numOfGames = this->m_database->getNumsOfPlayerGames(username);
	int numOfWins = this->m_database->getNumOfWins(username);
	result.push_back(username);
	result.push_back(std::to_string(numOfGames));
	result.push_back(std::to_string(numOfWins));
	return result;
}
