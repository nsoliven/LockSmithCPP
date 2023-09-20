/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

const int keyLength = 16;

class UserInterface{
public:
    void mainMenu(){
        cout<< " Welcome to your password manager! " << endl;
        cout<< "-------------------------------------" << endl;
        //list all options for the passwords:
    }
    string getPassword(){
        cout << "Enter your password:" << endl;
    }
};
class UserAuthentication{
public:
    string KeyGenerator(int length){
        string key = "";

        const string charset = 
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(0,charset.size()-1);

        for(int i = 0; i<length; i++){
            key = key+charset[distribution(generator)];
        }
    }
    void Auth(){
        
    }

};

class Encryption {
public:
    //
};


int main(){


    return 0;
}