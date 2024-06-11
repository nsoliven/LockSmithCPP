/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>



/*

Complete WIP!

*/

class Encryption {
public:
    // Define the AES encryption and decryption functions
    std::string aes_encrypt(const std::string plainText, const std::string key);
    std::string aes_decrypt(const std::string cipherText, const std::string key);
    std::string deriveKey(const std::string masterPassword);

    
    // Define the key generation function
    std::string generateKey(int length);
    
};

#endif