#pragma once

#include <exception>
#include <string>

class TakiException : public std::exception
{
public:
	TakiException(std::string err);
	const char* what();

	private:
		std::string error;
};