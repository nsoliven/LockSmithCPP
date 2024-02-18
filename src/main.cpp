/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


#include "userInterface.h"
#include "encryptionAlgorithm.h"
#include "passwordmanagement.h"



using namespace std;

const int keyLength = 16;

int main(){
    // show the main menu

    Database passDB;

    passDB.declareDatabase("passwords.db");

    

    UserInterface ui;
    ui.openMainMenu();
    string password;
    cin >> password;


    

    


    return 0;
}