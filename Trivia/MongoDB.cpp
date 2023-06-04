#include "MongoDB.h"


MongoDB::MongoDB()
{
    WSADATA wsaData;
    int wsaret = WSAStartup(0x0202, &wsaData);
    if (wsaret != 0)
    {
        throw std::exception(std::runtime_error("WSAStartup failed"));
    }
    mongocxx::instance instance{};
}

MongoDB::~MongoDB()
{
}

bool MongoDB::open()
{
    this->_client = mongocxx::client{ mongocxx::uri{} };
    mongocxx::database db = this->_client[DB_NAME];
    return true;
}

bool MongoDB::close()
{
    return true;
}

int MongoDB::doesUserExist(std::string username)
{
    try
    {
        std::vector<std::string> dbNames = this->_client.list_database_names();
        if (std::find(dbNames.begin(), dbNames.end(), std::string(DB_NAME)) == dbNames.end())
        {
            return false;
        }

        if (!this->_client[DB_NAME].has_collection(USERS_COLLECTION))
        {
            return false;
        }

        bsoncxx::document::value query = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", username));

        mongocxx::cursor result = this->_client[DB_NAME][USERS_COLLECTION].find(query.view());
        return std::distance(result.begin(), result.end());
    }
    catch (const mongocxx::operation_exception& ex) {
        std::cerr << "Exception from mongo: " << ex.what() << std::endl;
    }
}

int MongoDB::doesPasswordMatch(std::string username, std::string password)
{
    try
    {
        std::vector<std::string> dbNames = this->_client.list_database_names();
        if (std::find(dbNames.begin(), dbNames.end(), std::string(DB_NAME)) == dbNames.end())
        {
            return false;
        }

        if (!this->_client[DB_NAME].has_collection(USERS_COLLECTION))
        {
            return false;
        }

        bsoncxx::document::value query = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", username)
            , bsoncxx::builder::basic::kvp("password", password));

        mongocxx::cursor result = this->_client[DB_NAME][USERS_COLLECTION].find(query.view());
        return std::distance(result.begin(), result.end());
    }
    catch (const mongocxx::operation_exception& ex) {
        std::cerr << "Exception from mongo: " << ex.what() << std::endl;
    }
}

int MongoDB::addNewUser(std::string username, std::string password, std::string email, const std::string address, const std::string phoneNumber, const std::string birthday)
{
    try
    {
        if (this->doesUserExist(username))
        {
            return 1;
        }

        mongocxx::collection collection = this->_client[DB_NAME][USERS_COLLECTION];
        bsoncxx::document::value doc_value = bsoncxx::builder::stream::document{}
            << "username" << username
            << "password" << password
            << "email" << email
            << "address" << address
            << "phoneNumber" << phoneNumber
            << "birthday" << birthday
            << bsoncxx::builder::stream::finalize;

        collection.insert_one(doc_value.view());
    }
    catch (const mongocxx::operation_exception& ex)
    {
        std::cerr << "MongoDB Exception: " << ex.what() << std::endl;
        throw(TriviaException("Error when accessing db"));
    }
    return 0;
}

int MongoDB::getNumsOfPlayerGames(std::string username)
{
    std::vector<std::string> dbNames = this->_client.list_database_names();
    if (std::find(dbNames.begin(), dbNames.end(), std::string(DB_NAME)) == dbNames.end())
    {
        return false;
    }

    if (!this->_client[DB_NAME].has_collection(STATISTICS_COLLECTION))
    {
        return false;
    }

    auto result = this->_client[DB_NAME][STATISTICS_COLLECTION].find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", username)));

    if (result) {
        bsoncxx::document::view d = bsoncxx::to_json(result);
    }
    

    

}

MongoDB& MongoDB::getDB()
{
    static MongoDB db = MongoDB();
    return db;
}
