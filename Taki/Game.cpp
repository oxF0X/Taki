#include "Game.h"

void Game::playCard(LoggedUser user, Card* card)
{
	this->m_currentPlayer = &user;

}

void Game::removePlayer(LoggedUser user)
{
	this->m_players.erase(&user);
}

void Game::DrawCards(int numOfCards)
{
	Card* temp_card = this->m_gameDeck.getCards().front();
	this->m_players[this->m_currentPlayer].m_PlayerDeck.addCard(temp_card);
	this->m_gameDeck.removeCard(temp_card);
}
