#include <unordered_map>
#include <string>

#include "User.h"

#ifndef TWITERAK_H
#define TWITERAK_H

class Twitterak
{
    public :

        void run() ;
    
    private :
        std::unordered_map<std::string,User> usersMap ;

        void logIn (std::vector<std::string>) ;
        void signUp(std::vector<std::string>) ;
        void showMenu();
        std::string help() const ;

        void userOptions  (const std::string&) ;
        bool deleteAccount(const std::string&) ;
}; 

#endif