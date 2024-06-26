/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/
#include "encryptionAlgorithm.h"

/**
 * @brief Using key, we will encrypt the text passed through and it will be hashed to be stored
 * 
 * @param secure_vector plainText to be encrypted
 * @param secure_vecto key to use to encrypt
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

//overload to use keyFromMaster on setup
std::string Encryption::encrypt(Botan::secure_vector<char> &plainText){
    return encrypt(plainText, keyFromMaster);
}


/**
 * @brief Using key, decrypt cipherText
 *  
 * @param string cipherText
 * @param secure_vector key
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
//overload to use keyFromMaster on setup
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
    Botan::secure_vector<char> key = hashAndSaltVec(masterPassword,decryptEncryptSalt,600000,32);
    keyFromMaster = key;
    key.clear(); //clear key from memory as soon as possible
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
    Botan::secure_vector<char> key = hashAndSaltVec(strToHash, salt, iterations, keyLength);
    std::string key_str = Botan::hex_encode(Botan::secure_vector<uint8_t>(key.begin(), key.end()));
    return key_str;
}
Botan::secure_vector<char> Encryption::hashAndSaltVec(Botan::secure_vector<char> &strToHash, const std::string &salt, const size_t iterations, const size_t keyLength){
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

    //hex encode the key and place in Botan::secure_vector<char>
    return Botan::secure_vector<char>(key.begin(), key.end());
}