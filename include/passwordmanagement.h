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

using namespace std;

// will be used to edit the database of passwords for storing
// and retrieving passwords using sqlite3

// creates a new database class for the actual management of the database
class Database{
public:
    // define the database functions
    bool declareDatabase(const char *filename);
    void openDatabase(const char *filename);
    void closeDatabase(const char *filename);
    void createTable(const char *filename);
    void createDatabase(const char *filename);
    bool checkIfDatabaseExists(const char *filename, sqlite3 *db);
    void insertData(string password, string username, string website, string key);
    void removeData(string password, string username, string website, string key);
    void editData(string password, string username, string website, string key);
    void retrieveData(string password, string username, string website, string key);
};


class PasswordManagement{
public:
    void addPassword(string password, string username, string website, string key);
    void removePassword(string password, string username, string website, string key);
    void editPassword(string password, string username, string website, string key);
    void getPassword(string password, string username, string website, string key);
};


#endif