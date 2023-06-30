#pragma once

#include <exception>
#include <iostream>

class ParsingExceprion : public std::exception
{
public:
	ParsingExceprion(std::string err);
	const char* what();

private:
	std::string error;
};