/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/



#ifndef PASSWORDMANAGEMENT_H
#define PASSWORDMANAGEMENT_H


#include "SQLiteCpp/SQLiteCpp.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

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
    bool newDatabase;
    bool declareDatabase();
public:
    // define the database functions
    // declare database
    Database(const std::string &dbFileName);
    bool checkIfDatabaseExists();
    bool getIfNewDatabase();
    bool addItem(const std::string &pass_name, const std::string &username, const std::string &password);
    bool removeItem(const std::string &pass_name);
    bool getItem(const std::string &pass_name,std::string &username,std::string &password);
    bool listItems(std::vector<std::string> &item_names);
};


class SystemPasswordManagement{
private:
    //const used for functions with "TYPE Argument"
    static constexpr int GET_PASSWORD_NAME = 0;
    static constexpr int GET_EMAIL_USERNAME = 1;
    static constexpr int GET_MASTERPASSWORD = 1;
    static constexpr int GET_REGULARPASSWORD = 0;
    static constexpr int MAX_PASSWORD_LENGTH = 255;
    static constexpr int MIN_MASTERPASS_LENGTH = 8;

    bool hasErrored = false;
    Database db;
    std::string masterPasswordHash;
public:
    SystemPasswordManagement(const std::string& dbFileName);
    bool masterPasswordSetup(const std::string& masterpasslocation);
    bool masterPasswordLogin(const std::string& masterpasslocation);
    bool isMasterPasswordFileGood(const std::string& masterpasslocation);
    bool getIfNewDatabase();
    std::string getPasswordFromUser(const int &type,const bool &hidden);
    std::string getStringFromUser(const int &type);
    bool addPassword();
    bool removePassword();
    bool viewPassword();
    bool listAllPasswords();
};


#endif // PASSWORDMANAGEMENT_H