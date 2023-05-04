#pragma once

#include <vector>
#include <string>
#include <iostream>

#define LOGIN_REQ 10
#define Signup_REQ 11


class IRequestHandler;

typedef struct RequestInfo
{
	int requestId;
	std::vector<uint8_t> buffer;
} RequestInfo;

typedef struct RequestResult
{
	std::vector<uint8_t> buffer;
	IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};

