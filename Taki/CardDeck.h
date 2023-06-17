#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Card.h"



class CardDeck
{
public:
	void addCard(Card* c);
	void removeCard(Card* c);
	std::vector<Card*> getCards() const;
	

private:
	std::vector<Card*> m_cards;
};

