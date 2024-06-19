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

/**
 * @brief creates a randomly generated salt using BOTAN
 *  
 * @param string saltLength in BYTES
 * @return salt after being hex encoded
 */
std::string Encryption::generateSalt(const int &saltLength){
    Botan::AutoSeeded_RNG generator;
    std::vector<uint8_t> salt(saltLength);
    generator.randomize(salt.data(), salt.size());
    return Botan::hex_encode(salt.data(), salt.size()); 
}


/**
 * @brief Generates a 32 byte hash off and returns a string.
 *  
 * @param string string to hash
 * @param string salt 
 * @param size_t iterations, default 600,000 is secure.
 * @return hashed string consisting of 64 hex digits (32 bytes)
 */
std::string Encryption::hashAndSalt(const std::string &strToHash, const std::string &salt, const size_t iterations = DEFAULT_ITERATIONS) {

    if(iterations<MIN_ITERATIONS){
        throw std::runtime_error("Input of less than " + std::to_string(MIN_ITERATIONS) + " iterations is not recommended for security\n");
    }

    if(iterations>MAX_ITERATIONS){
        throw std::runtime_error("Input of more than " + std::to_string(MAX_ITERATIONS) + " iterations is not recommended\n");
    }
    
    const size_t key_length = 32; // Length of the derived key, 32 is considered secure for Argon2
    const std::string pbkdf_algo = "Argon2id";


    //create botan pwd fam. creates a unique ptr
    auto pwd_fam = Botan::PasswordHashFamily::create(pbkdf_algo);
    if (!pwd_fam) {
        throw std::runtime_error("PasswordHashFamily creation failed");
    }

    //create hash 
    auto pwd_hash = pwd_fam->from_iterations(iterations);

    std::vector<uint8_t> key(key_length);
    std::vector<uint8_t> salt_vec(salt.begin(), salt.end());

    pwd_hash->derive_key(key.data(), key.size(), strToHash.data(), strToHash.size(), salt_vec.data(), salt_vec.size());

    return Botan::hex_encode(key.data(), key.size());
}

/**
 * @brief The function effectively overwrites the sensitive string data in memory with random bytes. 
 *        This makes it significantly more difficult for an attacker to recover the original password if they gain access to the system's memory.
 * 
 * NOTE: this is not meant to be 100% secure as there are other neuances to memory attacks. 
 *       these memory attacks are out of scope for the security of this project.
 * 
 *       Some sophisticated techniques could potentially recover data even after it's overwritten.
 *       However, such attacks will be complex and often require significant resources and access to the target system.
 * 
 * @param string string to be replaced just in case of a memory hack
 * @return none
 */
void Encryption::secureEnoughMemoryDelete(std::string &str){
    Botan::AutoSeeded_RNG rng; // Create an RNG
    size_t length = str.size(); // Determine the length of the string
    Botan::secure_vector<uint8_t> random_bytes = rng.random_vec(length); // Generate random bytes

    for (size_t i = 0; i < length; ++i) {
        str[i] = static_cast<char>(random_bytes[i]); 
    }

    // Force a read (to discourage optimization) 
    volatile char &dummy = str[0]; // Use a volatile reference to str
    (void)dummy; // Avoid "unused variable" warnings
}
