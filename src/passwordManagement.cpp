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
 * @param username string&, used to store username
 * @param passwordEncrypted string&, used to store passwordEncrypted. Does not handle decryption. 
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
 * @brief Gets all the items in a DB then stores inside of a vector
 * 
 * @param vector<std::string> &item_names. Where to store items
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


bool SystemPasswordManagement::isMasterPasswordFileGood(const std::string& masterPassLocation){
    std::ifstream file(masterPassLocation);
    return file.good();

}
/**
 * @brief Used for grabbing password from user from console input
 *        Console input is hidden to prevent visual stealing of password with bool
 * 
 *        Password not hashed here yet, it is stored in plain text and is vulnerable in memory. 
 *        Unsafe until SystemPasswordManagement/Function User clears the returned secure vector once done with use.
 *
 * @param type Type of password we are getting,
 *        0 = (default) get password for regular storing
 *        1 = get master password
 * @param hidden bool if to hide data or not, default true
 * @return string of password grabbed
 */
Botan::secure_vector<char> SystemPasswordManagement::getPasswordFromUser(const int &type=1, const bool &hidden = true){
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

    Botan::secure_vector<char> secure_password;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        secure_password.push_back(ch);
    }

    if(secure_password.size() < 1 || secure_password.size() > MAX_PASSWORD_LENGTH){
        std::cerr << "BAD LENGTH, 1 <= PASSWORD <= "<< MAX_PASSWORD_LENGTH << std::endl;
        continue;
    }

    if (!secure_password.empty() && secure_password.back() == '\n') { 
        secure_password.pop_back();
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

    return secure_password;
    }

}

/**
 * @brief Used for basic strings from console. Ex. password name and username / email
 * 
 *
 * @param int type of string to get. ex 0 = password name, 1 = username
 * @param hidden bool if to hide data or not, default true
 * @return string of password grabbed
 */
std::string SystemPasswordManagement::getStringFromUser(const int &type = 0){
    switch(type){
        case 0:
        std::cout<<"Enter your a name for your password: ";
            break;
        case 1:
        std::cout<<"Enter your Username/Email: ";
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
 * @brief Used for building masterPassword hash and salt. Stores in hash file safely.
 * 
 * @return Bool if setup successful!
 */
bool SystemPasswordManagement::masterPasswordSetup(const std::string& masterPassLocation){

    if(isMasterPasswordFileGood(masterPassLocation)){
        //if file good that means masterPassLocationfile existed already thus not new instance
        std::cerr << "Error: MasterPassFile already exists, not new instance" << std::endl;
        return false;
    }

    //create outfile
    std::ofstream outFile(masterPassLocation);
    if (!outFile) {
        std::cerr << "Error: Unable to open file for writing. Did you give write permissions?" << std::endl;
        return false;
    }
    
    //setup part of masterPassword
    bool masterPasswordStillSettingUp = true;
    while(masterPasswordStillSettingUp){
        Botan::secure_vector<char> password = getPasswordFromUser(GET_MASTERPASSWORD,true);

        if(password.size() < MIN_MASTERPASS_LENGTH){
            std::cout << "We recommend that you create a password longer than " <<
            MIN_MASTERPASS_LENGTH << " Please re-enter a different password" << std::endl;
            continue;
        }

        std::cout << "Please enter your password again to confirm" << std::endl;
        Botan::secure_vector<char>  passwordConfirmation = getPasswordFromUser(GET_MASTERPASSWORD,true);

        if(passwordConfirmation!=password){
            std::cout << "Passwords did not match.. restarting setup" << std::endl << std::endl ;
            continue;
        }
        // if passwords match then get iterations and hash and store.
        std::cout << "--------------------------" << std::endl;
        std::cout << "\nChoose MasterPassword Hashing Iterations ("<<MIN_ITERATIONS<<" - " << MAX_ITERATIONS << ")\n";
        std::cout << "(Press Enter for the default of "<< DEFAULT_ITERATIONS <<" iterations.)\n";
        std::cout << "(More iterations make your password more secure, but will take longer to process)\n";
        std::cout << "\nEnter iterations choice: ";


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
                hashing = false;
            }catch(std::runtime_error& e){
                std::cerr << e.what() << "Using default iterations instead." << std::endl;
                iterations = DEFAULT_ITERATIONS; // replace with default iteration
            }
        }
        std::string salt2 = enc.generateSalt(16); // generate a second salt for AES256_ENCRYPT!
        outFile << hashedMasterPassword << ':'
                << salt << ':'
                << iterations << ':'
                << salt2;
        outFile.close();
        masterPasswordStillSettingUp = false;
    }
    return true;
}

/**
 * @brief PasswordManagerPrompts a login. Will also derive key for encryption algorithm
 *  
 * @return Bool if success
 */
bool SystemPasswordManagement::masterPasswordLogin(const std::string& masterPassLocation){
    std::ifstream inFile(masterPassLocation);
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

    if (tokens.size() != 4) {
        std::cerr << "Error: Invalid format in masterFile. Your FileSystemIsCorrupt\n";
        return false;
    }

    std::string fileHash = tokens[0];
    std::string fileSalt = tokens[1];
    std::string iterations = tokens[2];
    std::string secondaryFileSalt = tokens[3];

    Botan::secure_vector<char> userInput = getPasswordFromUser(1, true);
    std::string userHashed = enc.hashAndSalt(userInput, fileSalt, stoi(iterations));
    if(fileHash==userHashed){
        enc.deriveKey(userInput,secondaryFileSalt); // DERIVE THE KEYS ONCE LOGGED IN 
        return true;
    }
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
        Botan::secure_vector<char> password = getPasswordFromUser(GET_REGULARPASSWORD,true);
        std::string passwordHash = enc.encrypt(password);
        password.clear(); // reduce time in memory


        if(!db.addItem(passwordName,emailUsername,passwordHash)){
            return false;
        }
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
    std::string passwordEncrypted = "";


    try{
        passwordName = getStringFromUser(GET_PASSWORD_NAME);
    }catch(const std::invalid_argument& e){
        std::cout << e.what();
        return false;
    }

    //if errored exit function false
    if(!db.getItem(passwordName,emailUsername,passwordEncrypted)){
        return false;
    }

    Botan::secure_vector<char> passwordDecrypted = enc.decrypt(passwordEncrypted);
    std::cout << "Password Details:\n"
        << "--------------------------\n"
        << "Password Name: " << passwordName << "\n"
        << "Email/Username: " << emailUsername << "\n"
        << "Password: ";  
        printSecureVector(passwordDecrypted);
        passwordDecrypted.clear(); // clear asap right after printing from memory
    std::cout << "\n" << "--------------------------\n";
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
        std::string emailUsername, passwordEncrypted;
        if (db.getItem(passwordName, emailUsername, passwordEncrypted)) {
            Botan::secure_vector<char> passwordDecrypted = enc.decrypt(passwordEncrypted);
            std::cout << "Password Details:\n"
            << "--------------------------\n"
            << "Password Name: " << passwordName << "\n"
            << "Email/Username: " << emailUsername << "\n"
            << "Password: ";  
            printSecureVector(passwordDecrypted);
            passwordDecrypted.clear(); // clear asap right after printing from memory
            std::cout << "\n" << "--------------------------\n";
        } else {
            std::cerr << "Error retrieving details for password: " << passwordName << "\n";
        }
    }
    return true;
}


bool SystemPasswordManagement::printSecureVector(Botan::secure_vector<char> secure_vector){
    for (char ch : secure_vector) {
            std::cout << ch;
            if(std::cout.fail()){
                return false;
            }
        }
    return true;
}
