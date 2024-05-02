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
    try{
        SQLite::Database db(filename, SQLite::OPEN_CREATE);
        return true;
    }catch(SQLite::Exception& e){
            return false;
        }
    }
    

    bool Database::declareDatabase(const std::string &filename){
        try{
            SQLite::Database passdb(filename, SQLite::OPEN_READWRITE);
            passdb.exec("CREATE TABLE COMPANY(ID INT PRIMARY KEY, NAME TEXT, AGE INT)");
        }catch(SQLite::Exception& e){
            return false;
        }
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
            std::cout << "Enter your master password, [Input is hidden]: \n";
        }
        if(type==0&&hidden){
            std::cout << "Enter your wanted password, [Input is hidden]: \n";
        }
        if(type==1&&!hidden){
            std::cout << "Enter your master password, [Input is NOT HIDDEN]: \n";
        }
        if(type==0&&!hidden){
            std::cout << "Enter your wanted password, [Input is NOT HIDDEN]: \n";
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

        std::string password;
        std::getline(std::cin, password);

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
