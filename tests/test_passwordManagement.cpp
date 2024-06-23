#include <gtest/gtest.h>
#include "passwordManagement.h"

TEST(DatabaseTest, AddPassword) {
    Database db("test.db");
    std::string name = "TestName";
    std::string username = "TestUsername";
    std::string password = "TestPassword";

    db.addItem(name, username, password);

    std::string storedPassword;
    std::string storedUsername;
    db.getItem(name, storedUsername, storedPassword);

    ASSERT_EQ(storedPassword, password);
    ASSERT_EQ(storedUsername, username);

    remove("test.db");
}

TEST(DatabaseTest, AddPasswordLargeValue) {
    Database db("test.db");
    std::string name = "TestName";
    std::string username = "TestUsername";

    std::string password;
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()";
    for (int i = 0; i < 100000; ++i) {
        password += charset[rand() % (sizeof(charset) - 1)];
    }

    db.addItem(name, username, password);
    std::string storedPassword;
    std::string storedUsername;
    db.getItem(name, storedUsername, storedPassword);
    ASSERT_EQ(storedPassword, password);
    ASSERT_EQ(storedUsername, username);

    remove("test.db");
}


TEST(DatabaseTest, RemovePassword) {
    Database db("test.db");
    std::string name = "TestName";
    std::string username = "TestUsername";
    std::string password = "TestPassword";

    db.addItem(name, username, password);
    db.removeItem(name);

    std::string storedPassword;
    std::string storedUsername;
    bool itemExists = db.getItem(name, storedPassword, storedUsername);

    ASSERT_FALSE(itemExists);

    remove("test.db");
}

TEST(DatabaseTest, ListPasswords) {
    Database db("test.db");
    std::string name1 = "TestName1";
    std::string name2 = "TestName2";
    std::string username = "TestUsername";
    std::string password = "TestPassword";

    db.addItem(name1, username, password);
    db.addItem(name2, username, password);

    std::vector<std::string> itemNames;
    db.listItems(itemNames);

    ASSERT_EQ(itemNames.size(), 2);
    ASSERT_EQ(itemNames[0], name1);
    ASSERT_EQ(itemNames[1], name2);

    remove("test.db");
}
