#include <cstddef>
#include <map>
#include <string>
#include <unordered_map>

#include "Date.h"
#include "Tweet.h"

#ifndef USER_H
#define USER_H
void lowerStr(std::string&);

class Twitterak;

class User {
    // friend void lowerStr(string &) ;
    friend class Twitterak;

public:
    User();
    User(std::string, std::string, std::string);

    void setFirsrName  (std::string);
    void setUserName   (std::string);
    void setLink       (std::string);
    void setPassword   (std::string); // rate password
    void setBiogarghy  (std::string);
    void setCountry    (std::string);
    void setPhoneNum   (std::string); // dose it need validation?
    void setHeaderColor(std::string); //e
    void addTweet      (std::string);
    void setBirthDate  (std::string);

    std::string getFirstName  () const;
    std::string getUserName   () const;
    std::string getLink       () const;
    std::string getPassword   () const;
    std::string getBiogarghy  () const;
    std::string getCountry    () const;
    std::string getPhoneNum   () const;
    std::string getHeaderColor() const;
    std::string getTweet(size_t = 1, size_t = 0); // why cant be const[]?

    void deleteTweet(std::string);
    void editTweet(std::string);
    void increaseLike(std::string, int);
    void retweet(User, size_t, std::string = "");

    std::string changeProfile(std::vector<std::string>&);

    std::string print(bool = 0) const;

private:
    std::string firsName;
    std::string userName;
    std::string password;
    std::string link;

    std::string biogarghy;
    std::string country;
    std::string phoneNumber;
    std::string headerColor;

    Date birthDate; // no member fucntion

    std::map<size_t, Tweet> tweetOfUser;
    size_t tweetNumber { 1 };
};

#endif