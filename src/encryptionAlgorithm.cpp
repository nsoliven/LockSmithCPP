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
std::string Encryption::aes_encrypt(const std::string &plainText, const std::string &key){
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
std::string Encryption::aes_decrypt(const std::string &cipherText, const std::string &key){
    std::string decryptedStr;
    return decryptedStr;
}

/**
 * @brief Create and return a key based from masterPassword string passed through
 *  
 * @param string masterPassword
 * @return key derived from masterPassword
 */
std::string Encryption::deriveKey(const std::string &masterPassword){
    std::string key;
    return key;
}


std::string Encryption::generateSalt(const int &saltLength){
    std::string key;
    return key;
}


/**
 * @brief returns a hashed string after passing a salt and str to hash
 *  
 * @param string string to hash
 * @param string salt 
 * @return hashed string
 */
std::string Encryption::hashAndSalt(const std::string &strToHash, const std::string &salt) {
    const size_t iterations = 100000; // Example iteration count, adjust based on your security needs
    const size_t key_length = 32; // Length of the derived key
    const std::string pbkdf_algo = "Argon2id";

    auto pwd_fam = Botan::PasswordHashFamily::create(pbkdf_algo);
    if (!pwd_fam) {
        throw std::runtime_error("PasswordHashFamily creation failed");
    }

    auto pwd_hash = pwd_fam->from_iterations(iterations);

    std::vector<uint8_t> key(key_length);
    std::vector<uint8_t> salt_vec(salt.begin(), salt.end());

    pwd_hash->derive_key(key.data(), key.size(), strToHash.data(), strToHash.size(), salt_vec.data(), salt_vec.size());

    return Botan::hex_encode(key.data(), key.size());
}
