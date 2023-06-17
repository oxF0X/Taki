#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Card.h"

class NormalCard: Card
{
public:
	NormalCard(unsigned int Color, unsigned int Num);
	unsigned int Color;
	unsigned int Num;

};

