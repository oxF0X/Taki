#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Card.h"

class ActionCard;
//  : Card
//{
//public:
//	ActionCard(std::string code);
//	std::string ActionCode;
//	bool isLegalToPlay(Card lastCard) override;
//};

class NormalCard : public Card
{
public:
	NormalCard(std::string code);
	bool isLegalToPlay(Card* lastCard) override;
	std::string code;

};



