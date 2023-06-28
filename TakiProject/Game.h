#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include "CardDeck.h"
#include "Card.h"
#include "LoggedUser.h"
#include "TriviaException.h"

#define MAX_CARDS 8

typedef struct GameData
{
	CardDeck m_PlayerDeck;
	unsigned int m_trunNumber;

} GameData;

class Game
{
public:
	Game(std::vector<std::string> players);	
	void playCard(LoggedUser user, Card card);
	void removePlayer(LoggedUser user);
	bool IsProgress() const;
	std::vector<std::string> getPlayers() const;
	std::string getWinner()const;
	std::map<std::string, std::vector<std::string>> getCardsByPlayer() const;
	Card  getCurrentCard() const;
	std::vector<std::string> originalPlayers;
private:
	void moveToNextPlayer();
	void DrawCards(int numOfCards);
	void hasCards(LoggedUser user);
	
	
	
	void changeDirection();
	void stopPlayer();

	LoggedUser* m_currentPlayer;
	CardDeck m_gameDeck;	
	Card m_currentCard;
	bool isProgress;
	int m_currentDirection;
	int plusTwo;
	bool isTaki;
	std::string winner;
	std::map<LoggedUser*, GameData> m_players;

};
