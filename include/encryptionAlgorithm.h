/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>



/*

Complete WIP!

*/
using namespace std;

class Encryption {
public:
    // Define the AES encryption and decryption functions
    string aes_encrypt(string plaintext, string key);
    string aes_decrypt(string ciphertext, string key);


    // Define the key generation function
    string generateKey(int length);
    
};

#endif