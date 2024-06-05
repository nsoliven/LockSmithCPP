# LOCKSMITH - A C++ Based Password Manager

**Skills Demonstrated:** C++, SQLite, SQL, Cryptography, Object-Oriented Programming

**(!DB MANAGEMENT DONE!)**

🔐 A minimalistic password manager application built with C++ and SQL for learning purposes.

## IMPORTANT NOTES:

1. **DATA IS NOT SECURE YET**
   - Data in the password manager is currently NOT hashed in any way.
   - Will be stored securely in the future, hashing and cryptography being worked on currently.

## User Installation

- Dependencies already included. Download is in the versions.

## User Compilation and Building
Windows:
- Please have CMAKE & GIT installed on your system for building
- Windows must have dos2unix to convert SQLiteCPP, Windows simply use VSCODE's CMAKE instead.

UNIX/LINUX Building:
- Please have CMAKE & GIT & GCC Compiler installed on your system for building
```bash
git clone https://github.com/nsoliven/LockSmithCPP
cd LockSmithCPP
git submodule init
git submodule update
mkdir build
cd build
cmake ..
cmake --build ./ --config Debug --target all 
./lockSmithAPP
```

Note: If ask git asks, trust the repo with command provided

## User Flow

1. **Encryption and Data Storage:**
   - Password to the manager, it's encrypted using a strong encryption algorithm (e.g., AES) using the Master Password as the key
   - Database contains list of accounts and passwords which are stored securely using said key
2. **Master Password:**
   - You set a master password during initial setup.
   - The master password is used directly as the data encryption key.
3. **Secure Authentication:**
   - When you open the password manager, you are prompted to enter your master password.
   - The entered master password is hashed and compared to the stored hash for authentication.
4. **Database Decryption:**
   - If the master password is correct, the password manager uses it to decrypt the database.
   - Your stored passwords are now accessible.

## Files and Components (All subject to change vastly)

| File Name               | Description                                                                                                       |
|-------------------------|-------------------------------------------------------------------------------------------------------------------|
| MAIN.CPP                | Initializes the PasswordManagement obj                                                                            |
| PASSWORDMANAGEMENT.CPP  | Contains the main logic for managing passwords, interacting with the database, and handling encryption/decryption |
| ENCRYPTION.CPP          | Handles encryption and decryption of passwords                                                                    |
| USERINTERFACE.CPP       | Contains UI printing instructions for the command line                                                            |
| Additional Header Files | Contain function declarations and class definitions                                                               |

### PASSWORDMANAGEMENT.CPP Classes

| Class Name               | Description                                                                               |
|--------------------------|-------------------------------------------------------------------------------------------|
| Database                 | Handles database operations (creation, opening, adding, removing, viewing items)          |
| SystemPasswordManagement | Handles master password setup, login, password retrieval, and password management actions |

### Database Class Objects and Variables

| Name         | Type           | Description                    |
|--------------|----------------|--------------------------------|
| dbConnection | Object/Pointer | Represents the opened database |
| dbFilePath   | String         | Path to the database file      |

### Database Class Methods

| Method Name  | Description                       |
|--------------|-----------------------------------|
| initializeDB | Initializes the database          |
| addItem      | Adds an item to the database      |
| removeItem   | Removes an item from the database |
| viewItem     | Views an item in the database     |

### SystemPasswordManagement Class Objects and Variables

| Name                 | Type     | Description                       |
|----------------------|----------|-----------------------------------|
| Hashed user password | String   | Stores the hashed user password   |
| Database Object      | Database | An instance of the Database class |

### SystemPasswordManagement Class Methods

| Method Name         | Description                                                   |
|---------------------|---------------------------------------------------------------|
| masterPasswordSetup | Sets up the master password                                   |
| masterPasswordLogin | Handles master password login                                 |
| getPasswordFromUser | Gets a password from the user (with options for hiding input) |
| addPassword         | Adds a password (calls the database)                          |
| removePassword      | Removes a password (calls the database)                       |
| editPassword        | Edits a password (calls the database)                         |
| viewItem            | Views an item (calls the database)                            |
| search              | Searches for passwords                                        |

## Dependencies:

**OpenSSL (3.1.3)**

- OpenSSL is used in this project to provide cryptographic functions.
- Website: [https://www.openssl.org](https://www.openssl.org/)

**SQLiteCpp**

- SQLiteCpp is a smart and easy to use C++ SQLite3 wrapper. Used for db management of passwords.
- Included in the lib folder.
