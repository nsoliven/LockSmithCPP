/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/

/*

    Full layout of how passmanager will work:
    1. User opens program then will check if a DB file exists or not
    (a) If it does not exist, it will create a new DB file
    (b) If it does exist, it will open the DB file

    2. User will be prompted to enter a password
    (a) If the password is correct, the user will be able to access the DB file
    (b) If the password is incorrect, the user will be prompted to enter the password again
    * note password will be hashed and salted stored in a txt file.

    3. Password will be used to generate a key for the AES encryption algorithm


*/


#include "userInterface.h"
#include "encryptionAlgorithm.h"
#include "passwordmanagement.h"



using namespace std;

const int keyLength = 16;

int main(){
    // show the main menu
    //UserInterface ui;
    //ui.openMainMenu();

    // getting the password securely
    SystemPasswordManagement systemPass;
    std::string password = systemPass.getPasswordFromUser(1, true);

    return 0;
}