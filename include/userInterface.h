/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NxSOLIVEN

*/
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <iostream>
#include <fmt/color.h>
#include <botan/secmem.h> //so ui can print out passwords with secure_vector<char> type

class UserInterface{
private:
    const std::string bold = "\033[1m";
    const std::string reset = "\033[0m";
    const std::string bright_blue = "\033[1;34m"; // Bright blue color for "LockSmith C++"
    const std::string red = "\033[1;31m"; // Red color for "MASTER PASSWORD"
    const std::string green = "\033[1;32m"; // Green color for "LockSmith C++"
public:
    void openMainMenu();
    void openLoginMenu();
    void openNewInstanceMenu();
    void openMyPasswordsMenu();
    void openAddPasswordMenu();
    void openRemovePasswordMenu();
    void openEditPasswordMenu();
    void masterPasswordSetupSuccess();
    void incorrectPassword();
    void incorrectChoice();
    void invalidInput();
    void clearScreenOutput();
    void singleLineOutput(const std::string &output, const char &color);
    void printPasswordDetails(const std::string &pass_name, const std::string &username, Botan::secure_vector<char> &password);
};


#endif