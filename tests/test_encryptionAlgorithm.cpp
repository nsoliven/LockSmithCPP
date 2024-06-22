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

    // Assert
    EXPECT_FALSE(encryptedText.empty());
    EXPECT_EQ(encryptedText.size(), plainText.size()); // Ensure the encrypted text has the same size as the plain text
    EXPECT_NE(encryptedText, plainText); // Ensure the encrypted text is not the same as the plain text
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