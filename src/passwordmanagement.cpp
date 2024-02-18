/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


// will be used to edit the database of passwords for storing
// and retrieving passwords

#include <passwordmanagement.h>
#include <sqlite3.h>


bool checkIfDatabaseExists(const char *filename , sqlite3 *db){
    // check if the database exists
    if (sqlite3_open(filename, &db) == SQLITE_OK){
        return true;
    }
    else{
        return false;
    }
}

bool Database::declareDatabase(const char *filename){
    // declare the database
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open(filename, &db);

    if (rc){
        cout << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }
    else{
        cout << "Database opened successfully" << endl;
        sqlite3_close(db);
        return true;
    }
}


// Define the password management functions