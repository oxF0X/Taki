// Trivia.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Server.h" 
#include "SqliteDatabase.h" 

int main()
{
    SqliteDatabase db;
    Server s(Server::getServer(&db));
    s.run();
}
