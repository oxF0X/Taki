#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Card.h"

class ActionCard: Card
{
public:
	ActionCard(std::string code);
	std::string ActionCode;
	
};

