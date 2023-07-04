#include <string>
#include <unordered_map>
#include <unordered_set>

#include "User.h"

#ifndef TWITERAK_H
#define TWITERAK_H

class Twitterak 
{
public:
    void run();

private:
    std::unordered_map<std::string, User> usersMap;
    std::string userName {} ;
    // std::unordered_map<std::string,std::unordered_set<std::string> > hashtagMap ;

    void logIn (std::vector<std::string>);
    void signUp(std::vector<std::string>);
    void help  (std::vector<std::string>); //const??

    std::string defaultAdd();
    std::string helpLogin () const;

    void userOptions  (const std::string&);
    bool deleteAccount(const std::string&);

    short int findUser (const std::vector<std::string>&);

    void goPrint        (std::vector<std::string>);
    void goTweet        (std::vector<std::string>);
    void goEditTweet    (std::vector<std::string>);
    void goDelTweet     (std::vector<std::string>);
    void goLikeTweet    (std::vector<std::string>);
    void goDisLkeTweet  (std::vector<std::string>);
    void goEditProfile  (std::vector<std::string>);
    
    // void addHashtag  ()
};

#endif