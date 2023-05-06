// Trivia.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include "Server.h" 
#include "SqliteDatabase.h" 

int main()
{
    SqliteDatabase db;
    Server s(&db);
    s.run();
}
