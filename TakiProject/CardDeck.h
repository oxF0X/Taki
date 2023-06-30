#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Card.h"

// This class are represents a player card deck
class CardDeck
{
public:
	void addCard(Card c);
	void removeCard(Card c);
	std::vector<Card>& getCards();
	

private:
	std::vector<Card> m_cards;
};

