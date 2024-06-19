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
 * NOTE: AUTOMATICALLY DESTROYS PLAINTEXT DURING CALL
 *  
 * @param string plainText to be encrypted
 * @param string key to use to encrypt
 * @return string of password encrypted item to store in database later on
 */
std::string Encryption::encrypt(Botan::secure_vector<char> &plainText, Botan::secure_vector<char> &key){
    std::vector<uint8_t> key_vec(key.begin(), key.end());
    std::vector<uint8_t> plain_vec(plainText.begin(), plainText.end());
    

    Botan::AutoSeeded_RNG rng;
    Botan::secure_vector<uint8_t> iv = rng.random_vec(16);
    
    auto encryptor = Botan::Cipher_Mode::create("AES-256/GCM", Botan::Cipher_Dir::Encryption);
    encryptor->set_key(key_vec);
    encryptor->start(iv);
    encryptor->finish(plain_vec);

    std::vector<uint8_t> cipher_text(iv.begin(), iv.end());
    cipher_text.insert(cipher_text.end(), plain_vec.begin(), plain_vec.end());

    return Botan::hex_encode(cipher_text);
}

std::string Encryption::encrypt(Botan::secure_vector<char> &plainText){
    return encrypt(plainText, keyFromMaster);
}
/**
 * @brief Using key, decrypt cipherText
 *  
 * @param string cipherText
 * @param string key
 * @return string of password unencrypted
 */
Botan::secure_vector<char> Encryption::decrypt(const std::string &cipherText, Botan::secure_vector<char> &key){
    Botan::secure_vector<uint8_t> cipher_vec = Botan::hex_decode_locked(cipherText);
    
    Botan::secure_vector<uint8_t> iv(cipher_vec.begin(), cipher_vec.begin() + 16);
    Botan::secure_vector<uint8_t> enc_text(cipher_vec.begin() + 16, cipher_vec.end());

    if (cipher_vec.size() < 16) {
        throw std::runtime_error("Ciphertext is too short");
    }

    Botan::secure_vector<uint8_t> key_vec(key.begin(), key.end());

    auto decryptor = Botan::Cipher_Mode::create("AES-256/GCM", Botan::Cipher_Dir::Decryption);
    decryptor->set_key(key_vec);
    decryptor->start(iv);
    
    decryptor->finish(enc_text);
    return Botan::secure_vector<char> (enc_text.begin(), enc_text.end());
}

Botan::secure_vector<char> Encryption::decrypt(const std::string &cipherText){
    return decrypt(cipherText, keyFromMaster);
}
/**
 * @brief Create and return a key based from masterPassword string passed through
 *  
 * 
 * @param secure_vector masterPassword
 * @return key derived from masterPassword
 */
void Encryption::deriveKey(Botan::secure_vector<char> &masterPassword,std::string &decryptEncryptSalt){
    std::string key = hashAndSalt(masterPassword,decryptEncryptSalt,600000,16);
    keyFromMaster.assign(key.begin(), key.end());
    this->decryptEncryptSalt = decryptEncryptSalt;
    keysInitialized = true;
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
 * @brief Generates a hash and returns a string.
 *  
 * @param secure_vector botan's secure vector
 * @param string salt 
 * @param size_t iterations, default 600,000 is secure.
 * @param size_t keylength in bytes
 * @return hashed string consisting of 64 hex digits (32 bytes)
 */
std::string Encryption::hashAndSalt(Botan::secure_vector<char> &strToHash, const std::string &salt, const size_t iterations, const size_t keyLength) {

    if(iterations<MIN_ITERATIONS){
        throw std::runtime_error("Input of less than " + std::to_string(MIN_ITERATIONS) + " iterations is not recommended for security\n");
    }

    if(iterations>MAX_ITERATIONS){
        throw std::runtime_error("Input of more than " + std::to_string(MAX_ITERATIONS) + " iterations is not recommended\n");
    }
    
    const std::string pbkdf_algo = "Argon2id";

    //create botan pwd fam. creates a unique ptr
    auto pwd_fam = Botan::PasswordHashFamily::create(pbkdf_algo);
    if (!pwd_fam) {
        throw std::runtime_error("PasswordHashFamily creation failed");
    }

    //create hash 
    auto pwd_hash = pwd_fam->from_iterations(iterations);

    Botan::secure_vector<uint8_t> key(keyLength);
    Botan::secure_vector<uint8_t> salt_vec(salt.begin(), salt.end());

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


std::string Encryption::getDecryptEncryptSalt(){
    return this->decryptEncryptSalt;
}