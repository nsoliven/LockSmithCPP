/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


// will be used to edit the database of passwords for storing
// and retrieving passwords

#include <passwordmanagement.h>

// Define the password management functions
    Database::Database(const std::string &dbFileName){
        this->dbFileName = dbFileName;
        this->newInstance = !checkIfDatabaseExists();
        if(this->newInstance){
            declareDatabase();
        }
    }

   bool Database::checkIfDatabaseExists(){
        std::ifstream file(this->dbFileName);
        return file.good();
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

    bool Database::getIfNewInstance(){
        return this->newInstance;
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
     * @param hidden bool if to hide data or not
     * @return string of password grabbed
     */

    std::string SystemPasswordManagement::getPasswordFromUser(int type=1, bool hidden = true){
        if(type==1&&hidden){
            std::cout << "Enter your master password, [Input is hidden]: ";
        }
        if(type==0&&hidden){
            std::cout << "Enter your wanted password, [Input is hidden]: ";
        }
        if(type==1&&!hidden){
            std::cout << "Enter your master password, [Input is NOT HIDDEN]: ";
        }
        if(type==0&&!hidden){
            std::cout << "Enter your wanted password, [Input is NOT HIDDEN]: ";
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
     * @brief Used for if user decides to setup a new system, we will store the password securely.
     *  
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
     * @brief PasswordManagerPrompts a login
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


        std::string userInput = getPasswordFromUser();

        if(masterPass==userInput){return true;}
        return false;
    }