#include "AuthorizationException.h"

AuthorizationException::AuthorizationException(std::string err) : error(err)
{
}

const char* AuthorizationException::what()
{
    return this->error.c_str();
}
