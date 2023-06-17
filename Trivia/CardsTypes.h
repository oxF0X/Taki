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

class NormalCard : Card
{
public:
	NormalCard(unsigned int Color, unsigned int Num);
	bool isLegalToPlay(Card* lastCard) override;
	unsigned int Color;
	unsigned int Num;

};



