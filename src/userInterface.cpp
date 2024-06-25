/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/
#include "userInterface.h"
//current work in progress

// define the main menu

void UserInterface::openNewInstanceMenu() {
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("Welcome to {}LockSmith C++{} by {}NSOLIVEN{}\n", bright_blue, reset, bright_blue, reset);
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("We have detected that this is your first time using {}LockSmith C++{}\n", bright_blue, reset);
    fmt::print("Please create a {}MASTER PASSWORD{} to login to {}LockSmith C++{}\n\n", bright_blue, reset, bright_blue, reset);
}

void UserInterface::openLoginMenu() {

    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("Welcome back to {}LockSmith C++{} by {}NSOLIVEN{}\n", bright_blue, reset, bright_blue, reset);
    fmt::print("Please enter your password to unlock the database\n");
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
}

void UserInterface::openMainMenu(){
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("Welcome back to {}LockSmith C++{} by {}NSOLIVEN{}\n", bright_blue, reset, bright_blue, reset);
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    std::cout << "1. Add a new password" << std::endl;
    std::cout << "2. View all passwords" << std::endl;
    std::cout << "3. View A password" << std::endl;
    std::cout << "4. Delete A password" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void UserInterface::masterPasswordSetupSuccess(){
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    std::cout << "Congratulations! Master-Password is now setup" << std::endl;
    std::cout << "Continuing to login..." << std::endl;
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
}

void UserInterface::incorrectPassword(){
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("{}Incorrect password. Please try again{}\n", red, reset);
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
}


void UserInterface::invalidInput(){
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("{}Incorrect input. Please enter a number{}\n", red, reset);
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
}

void UserInterface::clearScreenOutput(){
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("{}Console Cleared. Thank you for using LockSmith by NSOLIVEN, Exiting the program{}\n", red, reset);
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
}

void UserInterface::singleLineOutput(const std::string &output, const char &color){
    std::string c;
    switch(color){
        case 'r':
            c = red;
            break;
        case 'g':
            c = green;
            break;
        default:
            c = bright_blue;
            break;
    }
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("{}{}{}\n", c, output, reset);
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
}

void UserInterface::printPasswordDetails(const std::string &pass_name, const std::string &username, Botan::secure_vector<char> &password){
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
    fmt::print("Password Name: {}\n", pass_name);
    fmt::print("Username: {}\n", username);
    fmt::print("Password: ");
    for (char c : password) {
        fmt::print("{}", c);
    }
    fmt::print("\n");
    fmt::print("{}{}--------------------------{}\n", bright_blue, bold, reset);
}