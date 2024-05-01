# LOCKSMITH - A C++ Based Password Manager (work in progress)
🔐 A minimalistic password manager application built with C++ and SQL for learning purposes.

## IMPORTANT NOTES:
1. **DATA IS NOT SECURE YET**
   - Data in the password manager is currently NOT hashed in any way. 
   - Will be stored secrurely in the future, development on database is first

## User Installation

- Dependencies already included. Download is in the versions.

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

**`encryptionAlgorithm.cpp`**
//

**`security.cpp`**
//

**`userInterface.cpp`**
//

**`main.cpp`**
//
- Main entry point of the program.
- Coordinates interactions between `userInterface`, `security`, and `encryptionAlgorithm` components.

**Additional Files (Header Files):**
- Header files contain function declarations and class definitions.

## Dependencies:

**'OpenSSL (3.1.3)'**
- OpenSSL is used in this project to provide cryptographic functions. 
- Website: [https://www.openssl.org](https://www.openssl.org/)
