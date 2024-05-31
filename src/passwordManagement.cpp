/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


// will be used to edit the database of passwords for storing
// and retrieving passwords

#include <passwordManagement.h>

// Define the password management functions
    Database::Database(const std::string &dbFileName = "lockSmithDB.db3")
    : dbFileName(dbFileName) , newInstance(!checkIfDatabaseExists())
    {
        if(this->newInstance){
            declareDatabase();
        }
    }

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

   bool Database::checkIfDatabaseExists(){
        std::ifstream file(this->dbFileName);
        return file.good();
    }

    bool Database::getIfNewInstance(){
        return this->newInstance;
    }
    /**
     * @brief Initialize the program's SystemPasswordManagement Class, Initialize DB object
     * 
     * @param filename string
     * @return N/A
     */

    SystemPasswordManagement::SystemPasswordManagement(const std::string &dbFileName = "lockSmithDB.db3")
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
    bool Database::viewItem(const std::string &pass_name) { 
        std::string username;
        std::string password;
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

    bool SystemPasswordManagement::isDatabaseNew(){
        return db.getIfNewInstance();
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
                std::cerr << "SystemPasswordManagemtn invalid type: " << type << std::endl;
                return "!errored!";
                break;
        }
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
        std::cout << std::endl;
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
            std::cout<<"Enter your";
                break;
            case 1:
                break;
        }




    }


    /**
     * @brief Used for if user decides to setup a new system, we will store the password securely.
     *  [UNSECURE]
     * @return Bool if setup successful!
     */

    bool SystemPasswordManagement::masterPasswordSetup(const std::string& masterpasslocation){

        std::ofstream outFile(masterpasslocation);
        if (!outFile) {
            std::cerr << "Error: Unable to open file for writing.\n";
            return false;
        }

        std::string password = "exmaple password"; // example password
        password = getPasswordFromUser();
        outFile << password << std::endl;

        return true;
    }

    /**
     * @brief PasswordManagerPrompts a login [UNSECURE]
     *  
     * @return Bool if success
     */
    bool SystemPasswordManagement::masterPasswordLogin(const std::string& masterpasslocation){
        //grab password from file
        std::ifstream inFile(masterpasslocation);
        if (!inFile) {
            std::cerr << "Error: Unable to open file for writing.\n";
            return false;
        }
        std::string masterPass;
        getline(inFile, masterPass);

        std::string userInput = getPasswordFromUser(1, true);

        if(masterPass==userInput){return true;}
        return false;
    }

    bool SystemPasswordManagement::addPassword(){
        getStringFromUser();
        getPasswordFromUser();
        return true;
    }

    bool SystemPasswordManagement::removePassword(){

        return true;
    }

    bool SystemPasswordManagement::viewPassword(){

        return true;
    }