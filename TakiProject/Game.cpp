#include "Game.h"

Game::Game(std::vector<std::string> players) : m_currentCard("00")
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	std::vector<std::string> cards  = { "Y1","Y2" "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9","YD","YP","YS","YT", "B1","B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9","BD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GD","GP","GS","GT", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9","RD","RP","RS","RT","Y1","Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9","YD","YP","YS","YT", "B1","B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9","BD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GD","GP","GS","GT", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9","RD","RP","RS","RT","CC","CC" ,"CC" ,"CC" };
	int size = cards.size();
	int random_index;

	for (int i = 0; i < players.size(); i++)
	{
		CardDeck temp;
		for (int j = 0; j < MAX_CARDS; j++)
		{
			random_index = std::rand() % size;
			temp.addCard( Card(cards[random_index]));
			cards.erase(cards.begin() + random_index);
			size--;
		}
		
		this->m_players[new LoggedUser(players[i])] = GameData{ temp, 0 };
		this->m_currentPlayer = m_players.begin()->first;
	}
	while(size != 0)
	{
		random_index = std::rand() % size;
		this->m_gameDeck.addCard(Card(cards[random_index]));
		cards.erase(cards.begin() + random_index);
		size--;
	}
	this->isProgress = true;
	this->m_currentDirection = 1;
	Card temp_card = this->m_gameDeck.getCards().front();
	this->m_currentCard = temp_card;
	this->m_gameDeck.removeCard(temp_card);
}

void Game::playCard(LoggedUser user, Card card)
{
	if (this->m_currentPlayer->getUsername() != user.getUsername())
	{
		throw(TriviaException(std::string("Wrong player")));
	}
	if (card.getCode() == "00")
	{
		if (this->plusTwo == 0)
		{
			this->DrawCards(1);
		}
		else
		{
			this->DrawCards(this->plusTwo);
			this->plusTwo = 0;
		}
		this->moveToNextPlayer();
		return;
	}

	if (!card.isLegalToPlay(this->m_currentCard))
	{
		throw(TriviaException(std::string("Ileagal move")));
	}
	LoggedUser* u;
	for (auto it : this->m_players)
	{
		if (it.first->getUsername() == user.getUsername())
		{
			u = it.first;
			break;
		}
	}
	if (std::find(this->m_players[u].m_PlayerDeck.getCards().begin(), this->m_players[u].m_PlayerDeck.getCards().end(), card) == this->m_players[u].m_PlayerDeck.getCards().end() || card.getCode()[1] == 'C')
	{
		throw(TriviaException(std::string("Card not exsit")));
	}

	if (card.getCode()[1] == 'P')
	{
		this->m_players[&user].m_PlayerDeck.removeCard(card);
		this->m_currentCard = card;
		return;
	}
	if (card.getCode()[1] == 'D')
	{
		this->changeDirection();
	}
	if (card.getCode()[1] == '2')
	{
		this->plusTwo += 2;
	}
	
	this->m_players[u].m_PlayerDeck.removeCard(card);
	this->m_currentCard = card;
	this->moveToNextPlayer();
}

void Game::removePlayer(LoggedUser user)
{
	//this->m_players.erase(std::remove_if(m_players.begin(), m_players.end(), [&](std::pair<LoggedUser*, GameData> u) { return u.first->getUsername() == user.getUsername(); }), m_players.end());
	auto it = m_players.begin();
	while (it != m_players.end()) {
		if (it->first->getUsername() == user.getUsername()) {
			it = m_players.erase(it);
		}
		else {
			++it;
		}
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
			cards.push_back(card.getCode());
		}
		players[(*it.first).getUsername()] = cards;	
	}
	return players;
}

Card Game::getCurrentCard() const
{
	return m_currentCard;
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
		Card temp_card = this->m_gameDeck.getCards().front();
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
	
}
