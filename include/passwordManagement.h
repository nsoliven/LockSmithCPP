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
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// will be used to edit the database of passwords for storing
// and retrieving passwords using sqlite3

// creates a new database class for the actual management of the database

class Database{
private:
    std::string dbFileName;
    bool newInstance;
public:
    // define the database functions
    // declare database
    Database(const std::string &dbFileName);
    bool declareDatabase();
    bool checkIfDatabaseExists();
    bool getIfNewInstance();
    bool addItem(const std::string &pass_name, const std::string &username, const std::string &password);
    bool removeItem(const std::string &pass_name);
    bool viewItem(const std::string &pass_name);
    bool listItems();
};


class SystemPasswordManagement{
private:
    Database db;
    std::string masterPasswordHash;
public:
    SystemPasswordManagement(const std::string &dbFileName);
    bool masterPasswordSetup(const std::string& masterpasslocation);
    bool masterPasswordLogin(const std::string& masterpasslocation);
    bool isDatabaseNew();
    std::string getPasswordFromUser(int type,bool hidden);
};


#endif