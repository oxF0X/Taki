#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include <typeinfo>

class Card
{
public:
	Card(std::string code);
	bool isLegalToPlay(Card lastCard);
	void setCode(std::string code);
	std::string getCode()const;
	bool operator==(Card other);
private:
	std::string code;
};