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
#include "passwordManagement.h"

const string dbName = ":memory:";
const string masterFile = "master_password";
const int keyLength = 16;
const unsigned int maxLoginAttempts = 5;
const unsigned int MASTER_PASSWORD_GET = 1;
const unsigned int REGULAR_PASSWORD_GET = 0;

int main(){
    //setup the main program with object's constructor
    SystemPasswordManagement systemPass(dbName);
    UserInterface ui;

    //check if we are setting up database and masterpassword
    if(systemPass.isDatabaseNew()){
        ui.openNewInstanceMenu();
        systemPass.masterPasswordSetup(masterFile);
    }else{ui.openLoginMenu();}

    //logging in 
    for(int i = 0; i <= maxLoginAttempts; i++){
        if(systemPass.masterPasswordLogin(masterFile)){break;}
        std::cout<< "Wrong Password! Attempts Left = [" <<
        (maxLoginAttempts-i) << " of " << maxLoginAttempts << "]\n";
        if(i==maxLoginAttempts){cout<< "MAX ATTEMPTS REACHED, EXITING PROGRAM\n"; return 1;}
    }


    //now logged in, OPEN MAIN MENU PAGE
    while(true){
        ui.openMainMenu();
        int choice = 0;
        if(std::cin >> choice){
            switch(choice){
            case 1: //ADD A PASSWORD
                break;
            case 2: //VIEW ALL PASSWORD
                break;
            case 3: //VIEW A PASSWORD
                break;
            case 4: // EXIT THE PROGRAM
                std::cout << std::endl << "Exiting the program" << std::endl;
                exit(0);
                break;
            default: // INVALID CHOICE
                std::cout << "Invalid choice" << std::endl;
                break;
            }
        }else{
            std::cout << "Invalid input, please enter a valid number." << std::endl;
        }
    }


    return 0;
}