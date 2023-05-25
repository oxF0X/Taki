// Trivia.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma comment (lib, "C:\\mongo-cxx-driver\\lib\\bsoncxx.lib")
#pragma comment (lib, "C:\\mongo-cxx-driver\\lib\\mongocxx.lib")


#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

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
    mongocxx::instance instance{};
    mongocxx::client client{ mongocxx::uri{} };
    


    MongoDB &db = MongoDB::getDB();
    Server s(Server::getServer(&db));
    s.run();
}
