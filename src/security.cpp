/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/
#include "security.h"
//work in progress

string UserAuthentication :: GenerateKey(){
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
