#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase()
{
	this->_db = nullptr;
}

SqliteDatabase::~SqliteDatabase()
{
    if (this->_db)
    {
        sqlite3_close(this->_db);   // Close DB
        this->_db = nullptr;
    }
}

bool SqliteDatabase::open()
{
    std::string dbFileName = DB_NAME;

    if (_access(dbFileName.c_str(), 0) == 0) 
    {
        return true;
    }

    if (sqlite3_open(dbFileName.c_str(), &(this->_db)) != SQLITE_OK)   // If can't open throw exception
    {
        std::cout << "Failed to open DB" << std::endl << "Exiting..." << std::endl;
        sqlite3_close(this->_db);
        this->_db = nullptr;
        return false;
    }

    char* errMessage = nullptr;
    const char* sqlStatement = "CREATE TABLE USERS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NAME TEXT NOT NULL, PASSWRD TEXT NOT NULL, EMAIL TEXT NOT NULL, ADDRESS TEXT NOT NULL, PHONE_NUMBER TEXT NOT NULL, BIRTHDAY DTAE NOT NULL);";

    if (sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, &errMessage) != SQLITE_OK)   // Check if the command was executed
    {
        std::cout << "Failed to create tables" << std::endl << "Exiting..." << std::endl;
        throw(AuthorizationException(std::string("Couldnt execute db query")));
        sqlite3_close(this->_db);
        return false;
    }

    return true;
}

bool SqliteDatabase::close()
{
    if (this->_db)
    {
        return false;
    }
    int res = sqlite3_close(this->_db);   // Close DB
    this->_db = nullptr;

    return res;
}

int SqliteDatabase::doesUserExist(std::string username)
{
    std::string sqlQuery = "SELECT * FROM USERS WHERE USERNAME = '" + username + "' LIMIT 1; ";
    char* errMessage = nullptr;

    std::string user;
    bool res = sqlite3_exec(this->_db, sqlQuery.c_str(), SqliteDatabase::userCallback, &user, &errMessage);

    if (res != SQLITE_OK)   // Check if the command was executed
    {
        throw(AuthorizationException(std::string("Couldnt execute db query")));
    }

    return user.size() != 0;
}

int SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
    std::string sqlQuery = "SELECT * FROM USERS WHERE USERNAME = '" + username  + "' AND PASSWORD = '" + password + "' LIMIT 1; ";
    char* errMessage = nullptr;

    std::string user ;
    bool res = sqlite3_exec(this->_db, sqlQuery.c_str(), SqliteDatabase::userCallback, &user, &errMessage);

    if (res != SQLITE_OK)   // Check if the command was executed
    {
        throw(AuthorizationException(std::string("Couldnt execute db query")));
    }

    return user.size() != 0;
}

int SqliteDatabase::addNewUser(std::string username, std::string password, std::string email, const std::string address, const std::string phoneNumber, const std::string birthday)
{
    if (this->doesUserExist(username))
    {
        return 1;
    }

    std::string sqlQuery = "INSERT INTO USERS(ID, NAME, PASSWORD, EMAIL, ADDRESS, PHONE_NNUMBER, BIRTHDAY) VALUES(NULL, '" + username + "', " + "'" + password + "', " + "'" + email + "', '" + address + "', '" + phoneNumber + "', '" + birthday + "' ); ";
    char* errMessage = nullptr;
    bool res = sqlite3_exec(this->_db, sqlQuery.c_str(), nullptr, nullptr, &errMessage);

    if (res != SQLITE_OK)   // Check if the command was executed
    {
        throw(AuthorizationException(std::string("Couldnt execute db query")));
    }
    return 0;
}

SqliteDatabase& SqliteDatabase::getDB()
{
    static SqliteDatabase db = SqliteDatabase();
    return db;
}

int SqliteDatabase::userCallback(void* ptr, int argc, char** argv, char** azColName)
{
    std::string *s = reinterpret_cast<std::string*>(ptr);
    *s = argv[0];
    *s += argv[1];
    *s += argv[2];
    return 0;
}
