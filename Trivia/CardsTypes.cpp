#include "CardsTypes.h"

//ActionCard::ActionCard(std::string code)
//{
//	this->ActionCode = code;
//}

NormalCard::NormalCard(std::string code)
{
	this->code = code;
}

bool NormalCard::isLegalToPlay(Card* lastCard)
{
	//if (typeid(*lastCard) == typeid(ActionCard()))
	//{
	//}
	if (typeid(*lastCard) == typeid(*this))
	{
		if (((NormalCard*)lastCard)->code[0] == this->code[0] || ((NormalCard*)lastCard)->code[1] == this->code[1]);
	}
	
	return false;
}


