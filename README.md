# LOCKSMITH - A C++ Based Password Manager
_Author: NSoliven_

**Skills Demonstrated:** `C++`, `SQLite`, `SQL`, `Cryptography with ARGON2`, `Botan`, `Object-Oriented Programming`

🔐 A minimalistic password manager application built with C++ and SQLite

## IMPORTANT NOTES ON SECURITY:

**PASSWORD SECURITY**
- Passwords are stored after being hashed/encrypted and salted (DEFAULT: `600,000` ITERATIONS)
  - Master Password is hashed with `ARGON2ID` stored in master_pass.hash along with salts and iterations, the user can choose iterations for Master Password.
    - _note on argon2: a state-of-the-art password hashing algorithm making it computationally expensive and time-consuming for attackers to crack._
  - Database Passwords (the user's passwords) are encrypted with `AES-256-GCM` using a key derived from the Master Password
    - _AES-256 is renowned for its exceptional strength, with a 256-bit key that makes it virtually unbreakable by brute-force attacks, even with the most powerful supercomputers._
 
**MEMORY SAFETY**
- Memory Safety using Botan's `Secure Vectors` where sensitive data occurs. The secure vectors are filled with random data as soon as possible and are not stored in swap at any time

**LOCALLY HOSTED**
- There are NO SERVERS that connect to your database at any time. All data is hosted within your private device ensuring maximum privacy and control

## User Installation
- Dependencies not needed, everything statically linked and included in executable files (lockSmithApp.exe and lockSmithApp.pm)

## User Compilation and Building
**Windows:**
- Please have CMAKE & GIT & CONAN installed on your system for building
- Locate your Conan profile at C:\Users\{USER}\.conan2\profiles
  - Change compiler.cppstd to compiler.cppstd=20
```sh
git clone https://github.com/nsoliven/LockSmithCPP
cd LockSmithCPP
conan install . --output-folder=build --build=missing --settings=build_type=Debug # change to 'Release' for release mode
cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -S . -B build
cmake --build build

#location may be different depending on how you build
cd ./out/build/windows_release
./lockSmithAPP.exe
```

**UNIX/LINUX Building:**
- Please have CMAKE & GIT & CONAN installed on your system for building
- Locate your Conan profile: The default profile is usually located in ~/.conan/profiles/default.
  - Change compiler.cppstd to compiler.cppstd=20
```bash
git clone https://github.com/nsoliven/LockSmithCPP
cd LockSmithCPP
conan install . --output-folder=build --build=missing --settings=build_type=Debug # change to 'Release' for release mode
cmake --build ./out/build/conan_release
#location may be different depending on how you build
cd ./out/build/conan_release
./lockSmithAPP
```
## Dependencies:

**BOTAN**

- Botan is used in this project to provide cryptographic functions and security
- Website: [https://botan.randombit.net/](https://botan.randombit.net/)

**SQLiteCpp**

- SQLiteCpp is a smart and easy to use C++ SQLite3 wrapper. Used for db management of passwords.
- Website: [https://github.com/SRombauts/SQLiteCpp/](https://github.com/SRombauts/SQLiteCpp)

# Files and Components (All subject to change vastly)

| File Name               | Description                                                                                                       |
|-------------------------|-------------------------------------------------------------------------------------------------------------------|
| MAIN.CPP                | Initializes the PasswordManagement obj                                                                            |
| PASSWORDMANAGEMENT.CPP  | Contains the main logic for managing passwords, interacting with the database, and handling encryption/decryption |
| ENCRYPTIONALGORITHM.CPP          | Handles encryption and decryption of passwords                                                                    |
| USERINTERFACE.CPP       | Contains UI printing instructions for the command line                                                            |
| Additional Header Files | Contain function declarations and class definitions                                                               |

## ENCRYPTIONALGORITHM.CPP Classes
### Encryption Class Objects and Variables

| Name              | Type                                | Description                                                                    |
|-------------------|------------------------------------|--------------------------------------------------------------------------------|
| `keyFromMaster`    | `Botan::secure_vector<char>` | Stores the derived encryption key from the master password.                       |
| `decryptEncryptSalt` | `std::string`                   | Stores the salt used for deriving the encryption/decryption key.                |
| `keysInitialized`  | `bool`                         | Indicates whether the encryption keys have been initialized from the master password. |

### Encryption Class Methods

| Method Name      | Description                                                                                                                               |
|------------------|-------------------------------------------------------------------------------------------------------------------------------------------|
| `encrypt`        | **Encrypts plaintext data using AES-256/GCM with a provided or derived key.** The method generates a random initialization vector (IV), performs the encryption, and returns the ciphertext as a hexadecimal-encoded string. |
| `decrypt`        | **Decrypts ciphertext using AES-256/GCM and a provided or derived key.** The method extracts the IV from the ciphertext, decrypts the data, and returns the plaintext as a `Botan::secure_vector<char>`.  |
| `deriveKey`      | **Derives an encryption key from the master password using Argon2id with a high iteration count and a specific salt.** The derived key is stored in `keyFromMaster` for later use. |
| `generateSalt`   | **Generates a random salt of a specified length in bytes using the Botan library.** The salt is returned as a hexadecimal-encoded string. |
| `hashAndSalt`    | **Hashes a password or string using Argon2id with a given salt and iteration count.** This method is used for both master password storage and key derivation. |


## PASSWORDMANAGEMENT.CPP Classes
### Database Class Objects and Variables

| Name         | Type               | Description                                                  |
|--------------|--------------------|--------------------------------------------------------------|
| `dbFileName`   | `std::string`      | Stores the file path to the SQLite database file.              |
| `newDatabase`  | `bool`             | Indicates if the database is new (true) or existing (false). |

### Database Class Methods

| Method Name        | Description                                                                                                                               |
|-------------------|-------------------------------------------------------------------------------------------------------------------------------------------|
| `declareDatabase()` | **Initializes and creates the database schema (tables, etc.) if it doesn't exist.** This is essential for a new database to ensure the correct structure is in place for storing password data. |
| `checkIfDatabaseExists()` | **Checks if the database file already exists on disk.** This helps determine whether the database needs to be initialized for the first time or if it can be opened as an existing database. |
| `getIfNewDatabase()` | **Returns a boolean value indicating whether the database is new (true) or already existed (false).** This information can be used by other parts of the code to determine the appropriate actions to take. |
| `addItem()`       | **Adds a new password entry to the database.** The method takes the password name, associated username/email, and the encrypted password as input and stores them in the database. |
| `removeItem()`    | **Removes a password entry from the database based on the provided password name.** This allows users to delete entries they no longer need. |
| `getItem()`       | **Retrieves a specific password entry from the database using the password name.** It returns the associated username/email and the encrypted password. |
| `listItems()`    | **Fetches all password names stored in the database and returns them as a vector of strings.** This is useful for displaying a list of available passwords to the user.  |


### SystemPasswordManagement Class Objects and Variables

| Name                    | Type     | Description                                                         |
|------------------------|----------|---------------------------------------------------------------------|
| `enc` (Encryption object) | `Encryption` | An instance of the `Encryption` class for cryptographic operations. |
| `db` (Database object)   | `Database`   | An instance of the `Database` class for database interactions.       |

### SystemPasswordManagement Class Methods

| Method Name        | Description                                                                                     |
|-------------------|-------------------------------------------------------------------------------------------------|
| `masterPasswordSetup`  | **Sets up the master password.** This includes hashing and salting the master password using Argon2id with the chosen number of iterations, then securely storing it alongside the salts in the `master_pass.hash` file. |
| `masterPasswordLogin` | **Handles master password login.** This verifies the entered master password against the stored hash and, if successful, derives the encryption key for decrypting passwords.   |
| `getPasswordFromUser` | **Securely obtains a password from the user.** This function includes options to hide input in the console for added privacy.       |
| `addPassword`      | **Adds a new password to the database.** This encrypts the password using AES-256 with the derived key before storage.        |
| `removePassword`   | **Removes a password from the database.**                                                        |
| `editPassword`     | **Edits an existing password in the database.**                                                     |
| `viewItem`        | **Retrieves and displays the details of a specific password entry.** The password is decrypted using AES-256 before being shown to the user.   |
| `search`          | **Searches for passwords in the database.**                                                     |
| `listAllPasswords`  | **Lists all password entries in the database, along with their decrypted details.**                                      |
| `printSecureVector` | **Helper function to print the contents of a `Botan::secure_vector<char>` to the console securely.**  |
