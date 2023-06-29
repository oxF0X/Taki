#include "Game.h"

Game::Game(std::vector<std::string> players) : m_currentCard("00"), m_database(&MongoDB::getDB())
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	std::vector<std::string> cards = { "CZ","CZ","ST", "ST", "Y1","Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9","YD","YP","YS","YT", "B1","B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9","BD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GD","GP","GS","GT", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9","RD","RP","RS","RT","Y1","Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9","YD","YP","YS","YT", "B1","B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9","BD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GD","GP","GS","GT", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9","RD","RP","RS","RT","CC","CC" ,"CC" ,"CC" };
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
	for (auto& it : this->m_gameDeck.getCards())
	{
		std::string code = it.getCode();
		if (it.getCode() != "ST" && code != "CC" && code != "CZ" && code[1] != 'T')
		{
			temp_card = it;
			break;
		}
	}
	this->m_currentCard = temp_card;
	this->m_gameDeck.removeCard(temp_card);
	this->m_currentPlayer = std::prev(m_players.end())->first;
	this->originalPlayers = players;
	this->isTaki = false;
}

void Game::playCard(LoggedUser user, Card card)
{
	if (!this->isProgress)
	{
		return;
	}

	if (this->m_currentPlayer->getUsername() != user.getUsername() && this->isProgress)
	{
		throw(TriviaException(std::string("Wrong player")));
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
	if (card.getCode() == "00")
	{
		this->hasCards(user);

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

	if (card.getCode() == "01")
	{
		this->isTaki = false;
		this->moveToNextPlayer();
		this->hasCards(user);
		return;
	}

	if (!card.isLegalToPlay(this->m_currentCard))
	{
		throw(TriviaException(std::string("Ileagal move")));
	}

	Card tmpCard = card.getCode();
	if (tmpCard.getCode()[1] == 'C')
	{
		tmpCard.setCode("CC");
	}
	if (std::find(this->m_players[u].m_PlayerDeck.getCards().begin(), this->m_players[u].m_PlayerDeck.getCards().end(), tmpCard) == this->m_players[u].m_PlayerDeck.getCards().end())
	{		
		throw(TriviaException(std::string("Card not exsit")));
	}

	if (card.getCode()[1] == 'P' || this->isTaki)
	{
		this->m_players[u].m_PlayerDeck.removeCard(card);
		this->m_currentCard = card;
		this->hasCards(user);
		return;
	}
	if (card.getCode() == "CZ")
	{
		this->m_players[u].m_PlayerDeck.removeCard(card);
		this->crazyCard();
		this->hasCards(user);
		this->moveToNextPlayer();
		return;
	}
	if (card.getCode() == "ST")
	{
		this->m_players[u].m_PlayerDeck.removeCard(card);
		std::string newCode = "";
		newCode += this->m_currentCard.getCode()[0];
		newCode += "T";

		this->m_currentCard.setCode(newCode);
		this->isTaki = true;
		this->hasCards(user);
		return;
	}

	if (card.getCode()[1] == 'T')
	{
		this->m_players[u].m_PlayerDeck.removeCard(card);
		this->m_currentCard = card;
		this->isTaki = true;
		this->hasCards(user);
		return;
	}

	if (card.getCode()[1] == 'S')
	{
		this->moveToNextPlayer();
		this->hasCards(user);
	}

	if (card.getCode()[1] == 'D')
	{
		this->changeDirection();
	}

	if (card.getCode()[1] == '2')
	{
		this->plusTwo += 2;
	}
	
	if (card.getCode()[1] == 'C')
	{
		this->m_players[u].m_PlayerDeck.removeCard(tmpCard);
	}
	else
	{
		this->m_players[u].m_PlayerDeck.removeCard(card);
	}

	this->m_currentCard = card;
	this->hasCards(user);
	this->moveToNextPlayer();
}

void Game::removePlayer(LoggedUser user)
{
	auto it = m_players.begin();

	if (this->m_currentPlayer->getUsername() == user.getUsername())
	{
		this->moveToNextPlayer();
	}



	while (it != m_players.end()) {
		if (it->first->getUsername() == user.getUsername()) {
			std::lock_guard<std::mutex>(this->_mtx);
			it = m_players.erase(it);
		}
		else {
			++it;
		}
	}

	if (this->m_players.size() == 1)
	{
		this->isProgress = false;
		this->m_database->writeResultToDB(this->originalPlayers, this->m_players.begin()->first->getUsername());
		this->winner = this->m_players.begin()->first->getUsername();
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

std::string Game::getWinner() const
{
	return this->winner;
}

std::string Game::getCurrentPlayer() const
{
	return this->m_currentPlayer->getUsername();
}

void Game::moveToNextPlayer()
{
	auto it = this->m_players.upper_bound(this->m_currentPlayer);
	if (this->m_currentDirection == -1) {
		auto it = this->m_players.lower_bound(this->m_currentPlayer);
	}
	if (it == this->m_players.end())
	{
		it = this->m_players.begin();
	}
	this->m_currentPlayer = (it)->first;
}

void Game::DrawCards(int numOfCards)
{
	for (int i = 0;  i < numOfCards;  i++)
	{
		Card temp_card = this->m_gameDeck.getCards().front();
		this->m_players[this->m_currentPlayer].m_PlayerDeck.addCard(temp_card);
		this->m_gameDeck.removeCard(temp_card);
		this->resetGameDeck();
	}

}

void Game::hasCards(LoggedUser user)
{
	if (this->m_players.size() == 0)
	{
		this->m_database->writeResultToDB(this->originalPlayers, this->m_currentPlayer->getUsername());
		this->isProgress = false;
		this->winner = user.getUsername();
		return;
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
	if (this->m_players[u].m_PlayerDeck.getCards().size() != 0)
	{
		return;
	}
	this->m_database->writeResultToDB(this->originalPlayers, (*u).getUsername());
	this->isProgress = false;
	this->winner = user.getUsername();
}

void Game::crazyCard()
{
	GameData first = this->m_players.begin()->second;
	for (auto it: this->m_players)
	{
		if (this->m_players.upper_bound(it.first) == this->m_players.end())
		{
			this->m_players[it.first] = first;
			return;
		}
		this->m_players[it.first] = this->m_players.upper_bound(it.first)->second;
	}

}

void Game::resetGameDeck()
{
	if (this->m_gameDeck.getCards().size() == 0)
	{
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		std::vector<std::string> cards = { "CZ","CZ","ST", "ST", "Y1","Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9","YD","YP","YS","YT", "B1","B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9","BD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GD","GP","GS","GT", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9","RD","RP","RS","RT","Y1","Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9","YD","YP","YS","YT", "B1","B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9","BD","BP","BS","BT", "G1","G3", "G3", "G4", "G5", "G6", "G7", "G8", "G9","GD","GP","GS","GT", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9","RD","RP","RS","RT","CC","CC" ,"CC" ,"CC" };

		int size = cards.size();
		int random_index;

		while (size != 0)
		{
			random_index = std::rand() % size;
			this->m_gameDeck.addCard(Card(cards[random_index]));
			cards.erase(cards.begin() + random_index);
			size--;
		}
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
