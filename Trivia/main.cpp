// Trivia.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#pragma comment (lib, "mongocxx.lib")
#pragma comment (lib, "bsoncxx.lib")
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Server.h" 
#include "SqliteDatabase.h" 



int main()
{
    SqliteDatabase db = SqliteDatabase::getDB();
    Server s(Server::getServer(&db));
    s.run();
}
