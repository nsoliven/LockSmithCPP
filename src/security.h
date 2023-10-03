/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/
#ifndef SECURITY_H
#define SECURITY_H

#include <string>
#include <iostream>

using namespace std;

class UserAuthentication{
private:
    const int keylength = 16;
public:
    string GenerateKey(int length){};
};

#endif