#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include <typeinfo>

class Card
{
	virtual bool isLegalToPlay(Card* lastCard) = 0; 
};