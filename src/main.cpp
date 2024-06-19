/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
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

const std::string dbName = "lockSmithDB.db3";
const std::string masterFile = "master_password.hash";
const int keyLength = 16;
const unsigned int maxLoginAttempts = 5;
const unsigned int MASTER_PASSWORD_GET = 1;
const unsigned int REGULAR_PASSWORD_GET = 0;

int main(){
    //setup the main program with object's constructor
    SystemPasswordManagement systemPass(dbName);
    UserInterface ui;

    //check if we are setting up database and masterpassword
    if(systemPass.getIfNewDatabase()){
        ui.openNewInstanceMenu();
        if(!systemPass.masterPasswordSetup(masterFile)){
            std::cerr << "UNABLE TO SETUP MASTERPASSWORD" << std::endl;
            return 1;
        }
        ui.masterPasswordSetupSuccess();
    }

    //logging in 
    ui.openLoginMenu();

    if(!(systemPass.isMasterPasswordFileGood(masterFile))){
        //if file good that means masterpasslocationfile does not EXIST thhus cant login?
        std::cerr << "Error: MasterPassFile does not exist. Is your filesystem corrupt?" << std::endl;
        return 1;
    }

    for(int i = 0; i <= maxLoginAttempts; i++){
        if(systemPass.masterPasswordLogin(masterFile)){break;}
        std::cout<< "Wrong Password! Attempts Left = [" <<
        (maxLoginAttempts-i) << " of " << maxLoginAttempts << "]\n";
        if(i==maxLoginAttempts){std::cout<< "MAX ATTEMPTS REACHED, EXITING PROGRAM\n"; return 1;}
    }


    //now logged in, OPEN MAIN MENU PAGE
    while(true){
        ui.openMainMenu();
        std::string userIn;
        std::getline(std::cin, userIn);
        try{
            int choice = std::stoi(userIn);
            switch(choice){
            case 1: //ADD A PASSWORD
                if(!systemPass.addPassword()){
                    std::cout << "Add password fail, restarting options" << std::endl;
                    continue;
                }
                std::cout << "Added password to database success! Showing options....." << std::endl;
                break;
            case 2: //VIEW ALL PASSWORD
                if(!systemPass.listAllPasswords()){
                    std::cout << std::endl << "List all password fail, restarting options" << std::endl;
                    continue;
                }
                break;
            case 3: //VIEW A PASSWORD
                if(!systemPass.viewPassword()){
                    std::cout << "View password fail, restarting options" << std::endl;
                    continue;
                }
                std::cout << std::endl << "View database password success! Showing options....." << std::endl;
                break;
            case 4: //DELETE A PASSWORD
                if(!systemPass.removePassword()){
                    std::cout << std::endl << "Remove password fail, restarting options" << std::endl;
                    continue;
                }
                std::cout << std::endl << "Remove password success! Showing options....." << std::endl;
                break;
            case 5: // EXIT THE PROGRAM
                #ifdef _WIN32  // If compiling for Windows
                    std::system("cls");
                    std::system("cls");
                #else
                    std::system("clear");
                    std::system("clear");
                #endif
                std::cout << std::endl << "Console Cleared. Thank you for using LockSmith, Exiting the program" << std::endl;
                exit(0);
                break;
            default: // INVALID CHOICE
                std::cerr << std::endl << "Invalid input, please enter a valid number." << std::endl;
                break;
            }
        }catch (const std::invalid_argument& e){
            std::cerr << std::endl << "Invalid input, please enter a valid number." << std::endl;
        }
    }


    return 1;
}