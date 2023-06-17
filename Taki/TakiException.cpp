#include "TakiException.h"

TakiException::TakiException(std::string err) : error(err)
{
}

const char* TakiException::what()
{
    return this->error.c_str();
}
