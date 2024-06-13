/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/


#include "encryptionAlgorithm.h"

#include <string>
#include <random>


/*
    Usage Notes:
    aes_encrypt and aes_decrypt called by SystemPasswordManagement
*/


/**
 * @brief Using key, we will encrypt the text passed through and it will be hashed to be stored
 *  
 * @param string plainText to be encrypted
 * @param string key to use to encrypt
 * @return string of password encrypted item to store in database later on
 */
std::string Encryption::aes_encrypt(const std::string plainText, const std::string key){
    std::string encryptedStr;
    
    return encryptedStr;
}

/**
 * @brief Using key, decrypt cipherText
 *  
 * @param string cipherText
 * @param string key
 * @return string of password unencrypted
 */
std::string Encryption::aes_decrypt(const std::string cipherText, const std::string key){
    std::string decryptedStr;
    return decryptedStr;
}

/**
 * @brief Create and return a key based from masterPassword string passed through
 *  
 * @param string masterPassword
 * @return key derived from masterPassword
 */
std::string Encryption::deriveKey(const std::string masterPassword){
    std::string key;
    return key;
}