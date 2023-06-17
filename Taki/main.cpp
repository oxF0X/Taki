// Trivia.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Server.h" 
#include "MongoDB.h"



int main()
{
    Server s(Server::getServer(&(MongoDB::getDB())));
    s.run();
}
