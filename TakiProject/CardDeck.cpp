#include "CardDeck.h"

void CardDeck::addCard(Card c)
{
	this->m_cards.push_back(c);
}

void CardDeck::removeCard(Card c)
{
	for (int i = 0; i < this->m_cards.size(); i++)
	{
		if (this->m_cards[i].getCode() == c.getCode())
		{
			this->m_cards.erase(this->m_cards.begin() + i);
			break;
		}
	}
}

std::vector<Card>& CardDeck::getCards()
{
	return this->m_cards;
}


