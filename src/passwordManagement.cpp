/*

Program under MIT License
Learn more @ https://github.com/nsoliven/locksmithcpp
Created in 2023 by NSOLIVEN

*/


// will be used to edit the database of passwords for storing
// and retrieving passwords

#include <passwordManagement.h>

// Define the password management functions

/**
 * @brief Constructor for Database Object.
 * Initializes database and saves if newInstance.
 * 
 * @param string dbFileName string
 */
Database::Database(const std::string &dbFileName)
: dbFileName(dbFileName) , newDatabase(!checkIfDatabaseExists())
{
    if(this->newDatabase){
        declareDatabase();
    }
}

/**
 * @brief Initializes database.
 * Not called outside of class
 * 
 * @return Bool if success or not
 */
bool Database::declareDatabase(){
    try{
        SQLite::Database passdb(this->dbFileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        passdb.exec("CREATE TABLE locksmithData ( \
                        password_name VARCHAR(255) PRIMARY KEY, \
                        email_username TEXT NOT NULL, \
                        password TEXT NOT NULL, \
                        date_added DATETIME DEFAULT CURRENT_TIMESTAMP \
                    );"
                );
    }catch(SQLite::Exception& e){
        std::cerr << "SQLite error: " << e.getErrorStr() << std::endl; // More detailed error message
        return false;
    }
    return true;
}

/**
 * @brief checks if the database exists BEFORE the constructor initializses
 * 
 * @return true if database exists
 */
bool Database::checkIfDatabaseExists(){
    std::ifstream file(this->dbFileName);
    return file.good();
}


/**
 * @brief getter for if newDatabase
 * 
 * @return true if newDatabase
 */
bool Database::getIfNewDatabase(){
    return this->newDatabase;
}

//-------------------------------

/**
 * @brief Constructor for SystemPasswordManagement, SystemPasswordManagement initializes
 * a DB object along with dbFileName
 * 
 * @param string dbFileName string
 */
SystemPasswordManagement::SystemPasswordManagement(const std::string &dbFileName)
: db(dbFileName){}

/**
 * @brief After user inputs all the data needed, addItem will store the data inside of the DB
 * 
 * @param pass_name const string&: Name of the password database entry
 * @param username const string&: Username Associated with password database entry
 * @param password const string&: Password Associated
 *  
 * @return if successful or not
 */
bool Database::addItem(const std::string &pass_name, const std::string &username, const std::string &password){
    try{
        SQLite::Database db(this->dbFileName, SQLite::OPEN_READWRITE);
        //First we will check if pass_name already existed
        std::string checkSql = "SELECT COUNT(*) FROM locksmithData WHERE password_name = ?";
        SQLite::Statement checkStmt(db, checkSql);
        checkStmt.bind(1, pass_name);
        
        if (checkStmt.executeStep() && checkStmt.getColumn(0).getInt() > 0) {
            std::cerr << "Password name '" << pass_name << "' already exists." << std::endl;
            return false;
        }

        std::string sql = "INSERT INTO locksmithData (password_name, email_username, password) VALUES (?, ?, ?)";
        SQLite::Statement stmt(db, sql);

        // Bind values to the placeholders
        stmt.bind(1, pass_name);
        stmt.bind(2, username);
        stmt.bind(3, password);

        // Execute the prepared statement
        stmt.exec();

    }catch (SQLite::Exception& e) { 
        std::cerr << "SQLite error adding item: " << e.what() << std::endl;
        return false;
    }
    return true;
}


/**
 * @brief Remove the password item with the name passed through
 * 
 * @param pass_name const string&: Name of the password database entry
 *  
 * @return if successful or not
 */
bool Database::removeItem(const std::string &pass_name) {
    try {
        SQLite::Database db(this->dbFileName, SQLite::OPEN_READWRITE);

        std::string sql = "DELETE FROM locksmithData WHERE password_name = ?";
        SQLite::Statement stmt(db, sql);
        stmt.bind(1, pass_name);
        
        int rowsAffected = stmt.exec(); // Get the number of rows deleted
        return rowsAffected > 0; // Return true if at least one row was deleted

    } catch (SQLite::Exception &e) {
        std::cerr << "SQLite error removing item: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief View the details of a specific password
 * 
 * @param pass_name const string&: Name of the password database entry
 *  
 * @return if successful or not
 */
bool Database::getItem(const std::string &pass_name,std::string &username,std::string &password) { 
    try {
        SQLite::Database db(this->dbFileName, SQLite::OPEN_READONLY);
        std::string sql = "SELECT email_username, password FROM locksmithData WHERE password_name = ?";
        SQLite::Statement stmt(db, sql);
        stmt.bind(1, pass_name);

        if (stmt.executeStep()) { // If the query returned a result
            username = stmt.getColumn(0).getString();
            password = stmt.getColumn(1).getString();
            return true;
        }
    } catch (SQLite::Exception &e) {
        std::cerr << "SQLite error viewing item: " << e.what() << std::endl;
    }
    return false; // Return false if no item was found or an error occurred
}

/**
 * @brief Lists all items in the db and saves in arr
 * 
 * @param string vector that will hold all items item_names
 *  
 * @return if successful or not
 */
bool Database::listItems(std::vector<std::string> &item_names){
    try {
        SQLite::Database db(this->dbFileName, SQLite::OPEN_READONLY);
        std::string sql = "SELECT password_name FROM locksmithData";
        SQLite::Statement stmt(db, sql);
        while (stmt.executeStep()) {
            item_names.push_back(stmt.getColumn(0).getString());
        }

        return true;
    } catch (SQLite::Exception &e) {
        std::cerr << "SQLite error listing items: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief checks db object inside if newInstance
 * 
 * @return true if new instance
 */
bool SystemPasswordManagement::getIfNewDatabase(){
    return db.getIfNewDatabase();
}


bool SystemPasswordManagement::isMasterPasswordFileGood(const std::string& masterpasslocation){
    std::ifstream file(masterpasslocation);
    return file.good();

}
/**
 * @brief Used for grabbing password from user from console input
 *        Console input is hidden to prevent visual stealing of password with bool
 * 
 *        Password not hashed here yet, it is stored in plain text and is vulnerable in memory.
 *
 * @param type Type of password we are getting,
 *        0 = (default) get password for regular storing
 *        1 = get master password
 * @param hidden bool if to hide data or not, default true
 * @return string of password grabbed
 */
std::string SystemPasswordManagement::getPasswordFromUser(const int &type=1, const bool &hidden = true){
    while(true){
        switch(type){
        case 0:
            if(hidden){
                std::cout << "Enter a password, [Input is hidden]: ";
            }else{std::cout << "Enter a password, [Input is NOT HIDDEN]: ";}
            break;
        case 1:
            if(hidden){
                std::cout << "Enter your master password, [Input is hidden]: ";
            }else{std::cout << "Enter your master password, [Input is NOT HIDDEN]: ";}
            break;
        default:
            std::cerr << "SystemPasswordManagement invalid type: " << type << std::endl;
            return "!errored!";
            break;
        }
        
    //used for hiding the user input
    if (hidden) {
        #ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
        DWORD mode = 0;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & (~(ENABLE_ECHO_INPUT)));
        #else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        #endif
    }

    std::string password = "";
    std::getline(std::cin, password);


    if(password.length() < 1 || password.length() > MAX_PASSWORD_LENGTH){
        std::cerr << "BAD LENGTH, 1 <= PASSWORD <= "<< MAX_PASSWORD_LENGTH << std::endl;
        continue;
    }

    if (!password.empty() && password.back() == '\n') { 
        password.pop_back();
    }

    if (hidden) {
        #ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
        DWORD mode = 0;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
        #else
        struct termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        oldt.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        #endif
        std::cout << std::endl;
    }
    return password;
    }

}

/**
 * @brief Used for grabbing password from user from console input
 *        Console input is hidden to prevent visual stealing of password with bool
 * 
 *        Password not hashed here yet, it is stored in plain text and is vulnerable in memory.
 *
 * @param type Type of password we are getting,
 *        0 = getPasswordName
 *        1 = getEmail
 * @param hidden bool if to hide data or not, default true
 * @return string of password grabbed
 */
std::string SystemPasswordManagement::getStringFromUser(const int &type = 0){
    switch(type){
        case 0:
        std::cout<<"Enter your Password NAME: ";
            break;
        case 1:
        std::cout<<"Enter your USERNAME/EMAIL: ";
            break;
        default:
            throw std::invalid_argument
            ("Invalid use of std::string SystemPasswordManagement::getStringFromUser");
    }

    std::string temp = "";
    std::getline(std::cin, temp);

    if (temp.size() < MAX_PASSWORD_LENGTH) {
        return temp;
    } else {
        throw std::out_of_range
        ("Input exceeds 254 characters. Please enter a shorter string.");
    }
}


/**
 * @brief Used for if user decides to setup a new system, we will store the password securely.
 *  [UNSECURE]
 * @return Bool if setup successful!
 */
bool SystemPasswordManagement::masterPasswordSetup(const std::string& masterpasslocation){

    if(isMasterPasswordFileGood(masterpasslocation)){
        //if file good that means masterpasslocationfile existed already thus not new instance
        std::cerr << "Error: MasterPassFile already exists, not new instance" << std::endl;
        return false;
    }

    //create outfile
    std::ofstream outFile(masterpasslocation);
    if (!outFile) {
        std::cerr << "Error: Unable to open file for writing. Did you give write permissions?" << std::endl;
        return false;
    }
    
    //setup part of masterPassword
    bool masterPasswordStillSettingUp = true;
    while(masterPasswordStillSettingUp){
        std::string password = ""; // example password
        std::string passwordConfirmation = ""; //confirm for later

        password = getPasswordFromUser(GET_MASTERPASSWORD,true);

        if(password.length() < MIN_MASTERPASS_LENGTH){
            std::cout << "We recommend that you create a password longer than " <<
            MIN_MASTERPASS_LENGTH << " Please re-enter a different password" << std::endl;
            continue;
        }

        std::cout << "Please enter your password again to confirm" << std::endl;
        passwordConfirmation = getPasswordFromUser(GET_MASTERPASSWORD,true);

        if(passwordConfirmation!=password){
            enc.secureEnoughMemoryDelete(password);
            enc.secureEnoughMemoryDelete(passwordConfirmation);
            std::cout << "Passwords did not match.. restarting setup" << std::endl << std::endl ;
            continue;
        }

        enc.secureEnoughMemoryDelete(passwordConfirmation); // delete asap after no use
        // if passwords match then get iterations and hash and store.
        std::cout << "\nEnter desired password hashing iterations (100,000 - " << MAX_ITERATIONS << "):\n";
        std::cout << "(Press Enter for the default of ("<< DEFAULT_ITERATIONS <<")\n";
        std::cout << "(More iterations make your password more secure, but will take longer to process)\n";

        std::string iterationInput;
        std::getline(std::cin, iterationInput);

        size_t iterations = DEFAULT_ITERATIONS;
        if (!iterationInput.empty()) {
            try{
                iterations = std::stoi(iterationInput);
            }catch(const std::invalid_argument& e) {
                std::cerr << "Invalid input. Using default iterations.\n";
            }catch(const std::out_of_range& e) {
                std::cerr << "Value outside allowed range. Using default iterations.\n";
            }
        }

        std::string salt = enc.generateSalt(16);
        std::string hashedMasterPassword;
        bool hashing = true;
        while(hashing){
            try{
                hashedMasterPassword = enc.hashAndSalt(password, salt, iterations);
                enc.secureEnoughMemoryDelete(password); // delete after hash is created
                hashing = false;
            }catch(std::runtime_error& e){
                std::cerr << e.what() << "Using default iterations instead." << std::endl;
                iterations = DEFAULT_ITERATIONS; // replace with default iteration
            }
        }
        outFile << hashedMasterPassword << ':'
                << salt << ':'
                << iterations;
        outFile.close();
        masterPasswordStillSettingUp = false;
    }
    return true;
}

/**
 * @brief PasswordManagerPrompts a login [UNSECURE]
 *  
 * @return Bool if success
 */
bool SystemPasswordManagement::masterPasswordLogin(const std::string& masterpasslocation){
    std::ifstream inFile(masterpasslocation);
    if (!inFile) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return false;
    }

    std::string line;
    getline(inFile, line); // Read the entire line

    // Split the line using the colon as the delimiter
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, ':')) {
        tokens.push_back(token);
    }

    if (tokens.size() != 3) {
        std::cerr << "Error: Invalid format in file. Expected hash:salt:iterations\n";
        return false;
    }

    std::string fileHash = tokens[0];
    std::string fileSalt = tokens[1];
    std::string iterations = tokens[2];

    std::string userInput = getPasswordFromUser(1, true);
    std::string userHashed = enc.hashAndSalt(userInput, fileSalt, stoi(iterations));
    enc.secureEnoughMemoryDelete(userInput);
    if(fileHash==userHashed){return true;}
    return false;
}


/**
 * @brief PasswordManagerPrompts a login
 *  
 * @return Bool if success
 */
bool SystemPasswordManagement::addPassword(){
    try{
        std::string passwordName = getStringFromUser(GET_PASSWORD_NAME);
        std::string emailUsername = getStringFromUser(GET_EMAIL_USERNAME);
        std::string password = getPasswordFromUser(GET_REGULARPASSWORD,true);
        if(!db.addItem(passwordName,emailUsername,password)){
            return false;
        }
        enc.secureEnoughMemoryDelete(password);
    }catch(const std::invalid_argument& e){
        std::cout << e.what();
        return false;
    }
    
    // else we return true since success
    return true;
}

/**
 * @brief PasswordManagerPrompts and handles DB for password removal
 *  
 * @return Bool if success
 */
bool SystemPasswordManagement::removePassword(){
    std::string passwordName = "";
    try{
        passwordName = getStringFromUser(GET_PASSWORD_NAME);
    }catch(const std::invalid_argument& e){
        std::cout << e.what();
        return false;
    }
    if(!db.removeItem(passwordName)){
        return false;
    }
    return true;
}

/**
 * @brief PasswordManagerPrompts and handles DB for password view
 *  
 * @return Bool if success
 */
bool SystemPasswordManagement::viewPassword(){
    std::string passwordName = "";
    std::string emailUsername = "";
    std::string password = "";

    try{
        passwordName = getStringFromUser(GET_PASSWORD_NAME);
    }catch(const std::invalid_argument& e){
        std::cout << e.what();
        return false;
    }

    //if errored exit function false
    if(!db.getItem(passwordName,emailUsername,password)){
        return false;
    }
    std::cout << "Password Details:\n"
        << "--------------------------\n"
        << "Password Name: " << passwordName << "\n"
        << "Email/Username: " << emailUsername << "\n"
        << "Password: " << password << "\n"
        << "--------------------------\n";
    enc.secureEnoughMemoryDelete(password);
    return true;
}

/**
 * @brief PasswordManager simply prints all names of passwords
 *  
 * @return Bool if success
 */

bool SystemPasswordManagement::listAllPasswords(){
    std::vector<std::string> pass_names_list;
    if(!db.listItems(pass_names_list)){
        return false;
    }
    std::cout << "Password Details:\n"
              << "--------------------------\n";
    for (unsigned int i = 0; i < pass_names_list.size(); ++i) {
        const std::string &passwordName = pass_names_list[i];
        std::string emailUsername, password;
        if (db.getItem(passwordName, emailUsername, password)) {
            std::cout << "Password Name: " << passwordName << "\n"
                      << "Email/Username: " << emailUsername << "\n"
                      << "Password: " << password << "\n";
            std::cout << "--------------------------\n";
        } else {
            std::cerr << "Error retrieving details for password: " << passwordName << "\n";
        }
    }
    return true;
}