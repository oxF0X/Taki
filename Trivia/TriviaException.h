#pragma once

#include <exception>
#include <string>

class TriviaException : public std::exception
{
public:
	TriviaException(std::string err);
	const char* what();

	private:
		std::string error;
};