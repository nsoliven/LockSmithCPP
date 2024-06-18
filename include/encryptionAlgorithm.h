/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <botan/pwdhash.h>
#include <botan/auto_rng.h>
#include <botan/rng.h>
#include <botan/hash.h>
#include <botan/hex.h>
#include <string>
#include <iostream>



/*

Complete WIP!

*/

class Encryption {
private:
public:
    // Define the AES encryption and decryption functions
    std::string aes_encrypt(const std::string &plainText, const std::string &key);
    std::string aes_decrypt(const std::string &cipherText, const std::string &key);
    std::string deriveKey(const std::string &masterPassword);
    std::string generateSalt(const int &saltLength);
    std::string hashAndSalt(const std::string &strToHash, const std::string &salt, const size_t iterations);

};

#endif