/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/
#include "userInterface.h"
//current work in progress

/*

We will use this file for all the interface functions.

*/




// define the main menu

void UserInterface::openNewInstanceMenu(){
    std::cout << "--------------------------" << std::endl;
    std::cout << "Welcome to LockSmith C++ by NSOLIVEN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "We have detected that this is your first time using LockSmith C++" << std::endl;
    std::cout << "Please create a MASTER PASSWORD to login to LockSmithC++" << std::endl << std::endl;
}

void UserInterface::openLoginMenu(){
    std::cout << "--------------------------" << std::endl;
    std::cout << "Welcome back to LockSmith C++ by NSOLIVEN" << std::endl;
    std::cout << "Please enter your password to unlock the database" << std::endl;
    std::cout << "--------------------------" << std::endl;
}
void UserInterface::openMainMenu(){
    std::cout << "--------------------------" << std::endl;
    std::cout << "Welcome to LockSmith C++ by NSOLIVEN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "1. Add a new password" << std::endl;
    std::cout << "2. View all passwords" << std::endl;
    std::cout << "3. View A password" << std::endl;
    std::cout << "4. Delete A password" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void UserInterface::masterPasswordSetupSuccess(){
    std::cout << "--------------------------" << std::endl;
    std::cout << "Congratulations! Master-Password is now setup" << std::endl;
    std::cout << "Continuing to login..." << std::endl;
    std::cout << "--------------------------" << std::endl;
}