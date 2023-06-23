#include "Game.h"

Game::Game(std::vector<std::string> players)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	std::vector<std::string> cards  = { "Y1","Y2" "Y3","Y4" , "Y5", "Y6", "Y7", "Y8", "Y9","YCD","YP","YS","YT", "B1","B2" "B3", "B4", "B5", "B6", "B7", "B8", "B9","BCD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GCD","GP","GS","GT", "R1", "R2", "R3","R4" , "R5", "R6", "R7", "R8", "R9","RCD","RP","RS","RT", "Y1","Y2" "Y3","Y4" , "Y5", "Y6", "Y7", "Y8", "Y9","YCD","YP","YS","YT", "B1","B2" "B3", "B4", "B5", "B6", "B7", "B8", "B9","BCD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GCD","GP","GS","GT", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9","RCD","RP","RS","RT","CC","CC" ,"CC" ,"CC" };
	int size = cards.size();
	int random_index;

	for (int i = 0; i < players.size(); i++)
	{
		CardDeck temp;
		for (int j = 0; j < MAX_CARDS; j++)
		{
			random_index = std::rand() % size;
			temp.addCard(new NormalCard(cards[random_index]));
			cards.erase(cards.begin() + random_index);
			size--;
		}
		
		this->m_players[new LoggedUser(players[i])] = GameData{ temp, 0 };
	}
	for (int i = 0; i < size; i++)
	{
		random_index = std::rand() % size;
		this->m_gameDeck.addCard(new NormalCard(cards[random_index]));
		cards.erase(cards.begin() + random_index);
		size--;
	}
	this->isProgress = true;
	this->m_currentDirection = 1;
}

void Game::playCard(LoggedUser user, Card* card)
{
	if (this->m_currentPlayer != &user)
	{
		throw(TriviaException(std::string("Wrong player")));
	}
	if (!card)
	{
		this->DrawCards(1);
		this->moveToNextPlayer();

	}
	if (!((NormalCard*)card)->isLegalToPlay(this->m_currentCard))
	{
		throw(TriviaException(std::string("Ileagal move")));
	}
	if (std::find(this->m_players[&user].m_PlayerDeck.getCards().begin(), 
		this->m_players[&user].m_PlayerDeck.getCards().end(), card) 
		== this->m_players[&user].m_PlayerDeck.getCards().end())
	{
		throw(TriviaException(std::string("Card not exsit")));
	}
	
	this->m_players[&user].m_PlayerDeck.removeCard(card);
	this->m_currentCard = card;
	this->moveToNextPlayer();
}

void Game::removePlayer(LoggedUser user)
{
	if (this->m_players.erase(&user) == 0)
	{
		throw(TriviaException(std::string("User not exsit")));
	}
}

bool Game::IsProgress() const
{
	return this->isProgress;
}

std::vector<std::string> Game::getPlayers() const
{
	std::vector<std::string> v;
	for ( auto it: this->m_players)
	{
		v.push_back((*it.first).getUsername());
	}
	return v;
}

std::map<std::string, std::vector<std::string>> Game::getCardsByPlayer() const
{
	std::map<std::string ,std::vector<std::string>> players;
	

	for (auto it : this->m_players)
	{
		std::vector<std::string> cards;
		for (auto card: it.second.m_PlayerDeck.getCards())
		{
			cards.push_back(((NormalCard*)card)->code);
		}
		players[(*it.first).getUsername()] = cards;	
	}
	return players;
}



void Game::moveToNextPlayer()
{
	auto it = this->m_players.upper_bound(this->m_currentPlayer);
	if (this->m_currentDirection == -1) {
		auto it = this->m_players.lower_bound(this->m_currentPlayer);
	}
	if (it != this->m_players.end())
	{
		this->m_currentPlayer = (it)->first;
	}
}

void Game::DrawCards(int numOfCards)
{
	for (int i = 0;  i < numOfCards;  i++)
	{
		Card* temp_card = this->m_gameDeck.getCards().front();
		this->m_players[this->m_currentPlayer].m_PlayerDeck.addCard(temp_card);
		this->m_gameDeck.removeCard(temp_card);
	}

}




void Game::changeDirection()
{
	if (this->m_currentDirection == 1)
	{
		this->m_currentDirection = -1;
	}
	else
	{
		this->m_currentDirection = 1;
	}
}

void Game::stopPlayer()
{
	this->moveToNextPlayer();
	this->moveToNextPlayer();
}
