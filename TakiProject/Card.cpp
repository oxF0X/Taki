#include "Card.h"

Card::Card(std::string code)
{
	this->code = code;
}

// This function checks if this card are valid to play  after the last card.
bool Card::isLegalToPlay(Card lastCard)
{
	if (lastCard.code[0] == this->code[0] || lastCard.code[1] == this->code[1] || this->code[1] == 'C' || this->code == "ST" || this->code == "CZ")
	{
		return true;
	}
	return false;
}

void Card::setCode(std::string code)
{
	this->code = code;
}

std::string Card::getCode() const
{
    return this->code;
}

bool Card::operator==(Card other)
{
	return this->code == other.getCode();
}
