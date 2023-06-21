#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include "CardDeck.h"
#include "CardsTypes.h"
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
	void playCard(LoggedUser user, Card* card);
	void removePlayer(LoggedUser user);
	bool IsProgress() const;
	std::vector<std::string> getPlayers() const;
	std::map<std::string, std::vector<std::string>> getCardsByPlayer() const;

private:
	void moveToNextPlayer();
	void DrawCards(int numOfCards);
	void removeCard(std::string cards[], int& size, int index);
	
	//void changeColor();
	void changeDirection();
	void stopPlayer();

	LoggedUser* m_currentPlayer;
	CardDeck m_gameDeck;	
	Card* m_currentCard;
	bool isProgress;
	int m_currentDirection;
	std::map<LoggedUser*, GameData> m_players;

};
