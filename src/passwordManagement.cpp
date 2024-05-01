/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


// will be used to edit the database of passwords for storing
// and retrieving passwords

#include <passwordmanagement.h>

// Define the password management functions
   bool Database::checkIfDatabaseExists(const std::string &filename){
    try{
        SQLite::Database db(filename, SQLite::OPEN_CREATE);
        return true;
    }catch(SQLite::Exception& e){
            return false;
        }
    }
    

    bool Database::declareDatabase(const std::string &filename){
        try{
            SQLite::Database passdb(filename, SQLite::OPEN_READWRITE);
            passdb.exec("CREATE TABLE COMPANY(ID INT PRIMARY KEY, NAME TEXT, AGE INT)");
        }catch(SQLite::Exception& e){
            return false;
        }
    }

    std::string SystemPasswordManagement::getPasswordFromUser(){
        std::string password;
        std::cin >> password;
    }
