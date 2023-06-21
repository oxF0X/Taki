#include "CardDeck.h"

void CardDeck::addCard(Card* c)
{
	this->m_cards.push_back(c);
}

void CardDeck::removeCard(Card* c)
{
	for (int i = 0; i < this->m_cards.size(); i++)
	{
		if (this->m_cards[i] == c)
		{
			std::vector<Card*>::iterator it = this->m_cards.begin() + i;
			this->m_cards.erase(it);
			delete this->m_cards[i];
			break;
		}
	}
}

std::vector<Card*> CardDeck::getCards() const
{
	return this->m_cards;
}


