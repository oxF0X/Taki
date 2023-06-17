#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "CardDeck.h"
#include "LoggedUser.h"

typedef struct GameData
{
	CardDeck m_PlayerDeck;
	unsigned int m_trunNumber;

} GameData;

class Game
{
public:
	void playCard(LoggedUser user, Card* card);
	void removePlayer(LoggedUser user);

private:
	void moveToNextPlayer();
	void DrawCards(int numOfCards);
	//void changeColor();
	//void changeDirection();
	//void stopPlayer();

	LoggedUser* m_currentPlayer;
	CardDeck m_gameDeck;
	unsigned int m_currentColor;
	//int m_currentDirection;
	std::map<LoggedUser*, GameData> m_players;

};
