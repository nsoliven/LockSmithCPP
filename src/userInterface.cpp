/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/
#include "userInterface.h"
//current work in progress

/*

We will use this file for all the interface functions.

list to do:
- openNewInstanceMenu
- openLoginMenu
- openMainMenu
- openAddPasswordMenu(s)
- openViewPasswordsMenu
- openExitMenu
*/




// define the main menu

void UserInterface::openNewInstanceMenu(){
    std::cout << "Welcome to LockSmith C++ by NSOLIVEN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "We have detected that this is your first time using LockSmith C++" << std::endl;
    std::cout << "Please create a new password to secure your passwords" << std::endl << std::endl;
}

void UserInterface::openLoginMenu(){
    std::cout << "Welcome back to LockSmith C++ by NSOLIVEN" << std::endl;
    std::cout << "Please enter your password to unlock the database" << std::endl;
    std::cout << "--------------------------" << std::endl;
}
void UserInterface::openMainMenu(){
    std::cout << "Welcome to the Password Manager" << std::endl;
    std::cout << "1. Add a new password" << std::endl;
    std::cout << "2. View all passwords" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    switch(choice){
        case 1:
            // add a new password
            break;
        case 2:
            // view all passwords
            break;
        case 3:
            // exit the program
            std::cout << std::endl << "Exiting the program" << std::endl;
            exit(0);
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
    }
}

