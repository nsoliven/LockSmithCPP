/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/



#ifndef PASSWORDMANAGEMENT_H
#define PASSWORDMANAGEMENT_H


#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <iostream>
#include <termios.h>


// will be used to edit the database of passwords for storing
// and retrieving passwords using sqlite3

// creates a new database class for the actual management of the database
class Database{
public:
    // define the database functions
    // declare database
    bool declareDatabase(const std::string &filename);
    bool checkIfDatabaseExists(const std::string &filename);
};


class SystemPasswordManagement{
public:

    std::string getPasswordFromUser();
};

class UserDatabasePasswordManager{
    void addPassword(std::string password, std::string username, std::string website, std::string key);
    void removePassword(std::string password, std::string username, std::string website, std::string key);
    void editPassword(std::string password, std::string username, std::string website, std::string key);
};

#endif