#include <gtest/gtest.h>
#include "encryptionAlgorithm.h"

TEST(EncryptionTest, EncryptPlainText) {
    Encryption enc;
    // Arrange
    Botan::secure_vector<char> plainText = {'H', 'e', 'l', 'l', 'o'};
    std::string salt = enc.generateSalt(16);
    std::string fakeMasterPassword = "fakeMasterPassword";
    Botan::secure_vector<char> vecMasterPass(fakeMasterPassword.begin(), fakeMasterPassword.end());

    std::string key = enc.hashAndSalt(vecMasterPass, salt, 600000, 16);
    Botan::secure_vector<char> keyVec(key.begin(), key.end());
    // Act
    std::string encryptedText = enc.encrypt(plainText, keyVec);
    std::string plainTextStr(plainText.begin(), plainText.end());

    // Assert
    EXPECT_FALSE(encryptedText.empty());
    EXPECT_NE(encryptedText, plainTextStr); // Ensure the encrypted text is not the same as the plain text
}

TEST(EncryptionTest, DecryptCipherText) {
    Encryption enc;
    // Arrange
    Botan::secure_vector<char> plainText = {'H', 'e', 'l', 'l', 'o'};
    std::string salt = enc.generateSalt(16);
    std::string fakeMasterPassword = "fakeMasterPassword";
    Botan::secure_vector<char> vecMasterPass(fakeMasterPassword.begin(), fakeMasterPassword.end());
    std::string key = enc.hashAndSalt(vecMasterPass, salt, 600000, 16);
    Botan::secure_vector<char> keyVec(key.begin(), key.end());

    // Act
    std::string encryptedText = enc.encrypt(plainText, keyVec);
    Botan::secure_vector<char> decryptedText = enc.decrypt(encryptedText, keyVec);

    // Assert
    EXPECT_FALSE(decryptedText.empty());
    EXPECT_EQ(decryptedText.size(), 5);
    EXPECT_EQ(decryptedText[0], 'H');
    EXPECT_EQ(decryptedText[1], 'e');
    EXPECT_EQ(decryptedText[2], 'l');
    EXPECT_EQ(decryptedText[3], 'l');
    EXPECT_EQ(decryptedText[4], 'o');
}

TEST(EncryptionTest, EncryptDecryptRandomStrings) {
    for (int i = 0; i < 3; i++) {
        Encryption enc;
        // Arrange
        std::string salt = enc.generateSalt(16);
        std::string fakeMasterPassword = "fakeMasterPassword";
        Botan::secure_vector<char> vecMasterPass(fakeMasterPassword.begin(), fakeMasterPassword.end());
        std::string key = enc.hashAndSalt(vecMasterPass, salt, 100000, 16);
        Botan::secure_vector<char> keyVec(key.begin(), key.end());

        // Generate a random string less than 255 characters
        int length = rand() % 255;
        std::string randomString;
        for (int j = 0; j < length; j++) {
            randomString += static_cast<char>(rand() % 26 + 'a');
        }
        Botan::secure_vector<char> vecRand(randomString.begin(), randomString.end());
        
        // Act
        std::string encryptedText = enc.encrypt(vecRand, keyVec);
        Botan::secure_vector<char> decryptedText = enc.decrypt(encryptedText, keyVec);

        // Assert
        EXPECT_FALSE(encryptedText.empty());
        EXPECT_NE(encryptedText, randomString);
        EXPECT_EQ(decryptedText, Botan::secure_vector<char>(randomString.begin(), randomString.end()));

        for (char c : decryptedText) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

