/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>

#include <openssl/aes.h>
#include <openssl/rand.h>

using namespace std;

class Encryption {
public:
    //
    string aes_encrypt();
    string aes_decrypt();
};

#endif