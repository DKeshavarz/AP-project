#include <string>
#include <map>

#include "Tweet.h"

#ifndef USER_H
#define USER_H
void lowerStr(std::string &) ;

class User
{
    //friend void lowerStr(string &) ;

    public :
        User();
        User (std::string ,std::string ,std::string ) ;

        void setFirsrName (std::string) ;
        void setUserName  (std::string) ;
        void setPassword  (std::string) ; 
        void setBiogarghy (std::string) ;
        void setCountry   (std::string) ; //not working
        void addTweet     (std::string) ;

        std::string getFirstName()const;
        std::string getUserName ()const;
        std::string getPassword ()const;
        std::string getBiogarghy()const;
        std::string getCountry  ()const;
        std::string getTweet (size_t = 1,size_t = 0);


        void deleteTweet(std::string) ;
        void editTweet  (std::string) ;

        std::string print ()const ;
        
    private :
        std::string firsName ;
        std::string userName ;       
        std::string password ;

        std::string biogarghy;
        std::string country  ;

        //phone number ;
        //date birthday ;
        
        std::map<size_t,Tweet> tweetOfUser ;
        size_t tweetNumber {1};

};

#endif