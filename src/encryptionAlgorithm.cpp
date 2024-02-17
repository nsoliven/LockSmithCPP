/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


#include "encryptionAlgorithm.h"

#include <string>
#include <random>

// aes_encrypt and aes_decrypt are the functions that will be used to encrypt and decrypt the password
string Encryption :: aes_encrypt(string key, string password){
    AES_KEY aesKey;
}
string Encryption :: aes_decrypt(string key, string password){

}

string Encryption :: generateKey(int length){
    string key = "";
    const string charset = 
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0,charset.size()-1);

    for(int i = 0; i<length; i++){
        key = key+charset[distribution(generator)];
    }
}