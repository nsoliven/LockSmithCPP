/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/


// will be used to edit the database of passwords for storing
// and retrieving passwords

#include <passwordmanagement.h>

// Define the password management functions
   bool Database::checkIfDatabaseExists(const std::string &filename){
        std::ifstream file(filename);
        return file.good();
    }
    

    bool Database::declareDatabase(const std::string &filename){
        try{
            SQLite::Database passdb(filename, SQLite::OPEN_READWRITE);
            passdb.exec("CREATE TABLE COMPANY(ID INT PRIMARY KEY, NAME TEXT, AGE INT)");
        }catch(SQLite::Exception& e){
            return false;
        }
        return true;
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
     * @param type T
     * @param 
     * @return If successfully setup the masterPassword for a new database.
     */

    bool SystemPasswordManagement::masterPasswordSetup(){

        std::ofstream outFile("master_password");
        if (!outFile) {
            std::cerr << "Error: Unable to open file for writing.\n";
            return false;
        }

        std::string password = "exmaple password"; // example password
        password = getPasswordFromUser();
        outFile << password << std::endl;

        return true;
    }
