#pragma once

#include <exception>
#include <string>

class AuthorizationException : public std::exception
{
public:
	AuthorizationException(std::string err);
	const char* what();

	private:
		std::string error;
};