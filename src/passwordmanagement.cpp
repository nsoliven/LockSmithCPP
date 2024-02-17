/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


// will be used to edit the database of passwords for storing
// and retrieving passwords

#include <passwordmanagement.h>
void Database::declareDatabase(){
    // declare the database
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open("passwords.db", &db);  //declare the database




}

void Database::openDatabase(){
    // open the database
}
void Database::closeDatabase(){
    // close the database
}


// Define the password management functions