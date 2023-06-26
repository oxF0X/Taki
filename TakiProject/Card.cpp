#include "Card.h"

Card::Card(std::string code)
{
	this->code = code;
}

bool Card::isLegalToPlay(Card lastCard)
{
	if (lastCard.code[0] == this->code[0] || lastCard.code[1] == this->code[1] || this->code[1] == 'C')
	{
		return true;
	}
	return false;
}

std::string Card::getCode() const
{
    return this->code;
}

bool Card::operator==(Card other)
{
	return this->code == other.getCode();
}
