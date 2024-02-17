/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/

#include <sqlite3.h>
#include <string>
#include <iostream>

using namespace std;


#ifndef PASSWORDMANAGEMENT_H
#define PASSWORDMANAGEMENT_H


// will be used to edit the database of passwords for storing
// and retrieving passwords using sqlite3

// creates a new database class for the actual management of the database
class Database{
public:
    // define the database functions
    void declareDatabase();
    void openDatabase();
    void closeDatabase();
    void createTable();
    void createDatabase();
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