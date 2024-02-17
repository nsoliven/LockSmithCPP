/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <iostream>

using namespace std;

class UserInterface{
public:
    void openMainMenu();
    void openLoginMenu();
    void openNewInstanceMenu();
    void openMyPasswordsMenu();
    void openAddPasswordMenu();
    void openRemovePasswordMenu();
    void openEditPasswordMenu();
};


#endif