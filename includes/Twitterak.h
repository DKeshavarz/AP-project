#include <string>
#include <unordered_map>
#include <unordered_set>

#include "User.h"

#ifndef TWITERAK_H
#define TWITERAK_H

class Twitterak {
public:
    void run();

private:
    std::unordered_map<std::string, User> usersMap;
    // std::unordered_map<std::string,std::unordered_set<std::string> > hashtagMap ;

    void logIn (std::vector<std::string>);
    void signUp(std::vector<std::string>);
    void help  (std::vector<std::string>); //const??

    std::string defaultAdd();
    std::string helpLogin () const;

    void userOptions  (const std::string&);
    bool deleteAccount(const std::string&);
    // void addHashtag  ()
};

#endif