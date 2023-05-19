#include "ParsingException.h"

ParsingExceprion::ParsingExceprion(std::string err) : error(err)
{
}

const char* ParsingExceprion::what()
{
    return this->error.c_str();
}
