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
    cout << "Welcome to LockSmith C++ by NSOLIVEN" << endl;
    cout << "--------------------------" << endl;
    cout << "We have detected that this is your first time using LockSmith C++" << endl;
    cout << "Please create a new password to secure your passwords" << endl << endl;
    cout << "Enter your new password: "; 
}

void UserInterface::openLoginMenu(){
    cout << "Welcome to LockSmith C++" << endl;

    //check if the password is correct
    

}

void UserInterface::openMainMenu(){
    cout << "Welcome to the Password Manager" << endl;
    cout << "1. Add a new password" << endl;
    cout << "2. View all passwords" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch(choice){
        case 1:
            // add a new password
            break;
        case 2:
            // view all passwords
            break;
        case 3:
            // exit the program
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
}

