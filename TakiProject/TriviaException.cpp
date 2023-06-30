#include "TriviaException.h"

TriviaException::TriviaException(std::string err) : error(err)
{
}

const char* TriviaException::what()
{
    return this->error.c_str();
}
