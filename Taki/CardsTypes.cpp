#include "CardsTypes.h"

//ActionCard::ActionCard(std::string code)
//{
//	this->ActionCode = code;
//}

NormalCard::NormalCard(unsigned int Color, unsigned int Num)
{
	this->Color = Color;
	this->Num = Num;
}

bool NormalCard::isLegalToPlay(Card* lastCard)
{
	if (typeid(*lastCard) == typeid(ActionCard()))
	{
	if (typeid(*lastCard) == typeid(*this))
	{
		if(((NormalCard*)lastCard)->Color == this->Color || ((NormalCard*)lastCard)->Num == this->Num);
	}

	return false;
}
