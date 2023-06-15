#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>


#include "Twitterak.h" 
#include "User.h" 
#include "Tweet.h"
#include "Date.h"

using namespace std ;

User::User ()
{}
User::User (string firsName,string userName,string password) :tweetNumber{1}
{
    setFirsrName(firsName) ;
    setUserName (userName) ;
    setPassword (password) ;
}
void  User::setFirsrName (string fName ) 
{
    firsName = fName ;
}
void User::setUserName   (string Uname) 
{   if (Uname[0] == '@')
    {
        if(Uname.size() < 6)
            throw invalid_argument("! Username is to short") ;
        else if('0' <= Uname[0] && Uname[0] <= '9')
            throw invalid_argument("! Username shouldn't start with numbers") ;

    }

    else 
    {
        if(Uname.size() < 5)
            throw invalid_argument("! Username is to short") ;
        else if('0' <= Uname[0] && Uname[0] <= '9')
            throw invalid_argument("! Username shouldn't start with numbers") ;
    }

    for(size_t i = 1 ; i < Uname.size() ; ++i)
    {
        if( !('0' <= Uname[i] && Uname[i] <= '9') && 
            !('a' <= Uname[i] && Uname[i] <= 'z') &&
            !('A' <= Uname[i] && Uname[i] <= 'Z'))
        {
            throw invalid_argument ("! Username contain invalic character") ;
        }
    }

    string reservedWord {"exit,help,login,edit,signup,logout,profile"} ;//it may contion more...//i add some

    if(reservedWord.find(Uname) != string::npos)
        throw invalid_argument ("! Username is a command!!") ;
    
    userName = Uname ;  
}
void User::setPassword  (string pas) 
{
    //rate password
    password = pas ;
} 
void User::setBiogarghy (string bio) 
{
    if(bio.size() < 160)
        biogarghy = bio ;
    else
        throw invalid_argument("! Len of biograghy is too long...") ;
}
void User::setCountry (string country)
{
    lowerStr(country) ;
    unordered_map<string,string> countryMap;
}
void User::addTweet (string inputTweetStr) 
{
    Tweet inputTweet (inputTweetStr);
    tweetOfUser[tweetNumber] = inputTweet ;
    tweetNumber++ ;
}
string User::getFirstName()const
{
    return firsName ;
}
string User::getUserName()const
{
    return userName ;
}
string User::getPassword()const
{
    return password ;
}
string User::getBiogarghy()const
{
    return biogarghy ;
}
string User::getCountry ()const
{
    return country;
}
string User::getTweet (size_t start , size_t end)
{
    end = end == 0 ? tweetNumber : end ;

    ostringstream outPut ;
    for(size_t i = start ; i < end ; ++i)
    {
        if(tweetOfUser.count(i))
            outPut << i << ')' << tweetOfUser[i].getTweetStr() <<"\t\t\t"<<"Likes: "<<tweetOfUser[i].tweetLikes << '\n' ;
    }

    if(outPut.str().empty())
        outPut << "! No tweet yet :) " ;

    return outPut.str();
}

void User::deleteTweet(string tweetNumStr) 
{
    size_t tweetNum = stoi(tweetNumStr) ;
    tweetOfUser.erase(tweetNum) ;
}
void User::editTweet  (string tweetNumStr) 
{
    size_t tweetNum = stoi(tweetNumStr) ;
    string newTweetStr {} ;

    cout << getTweet(tweetNum,tweetNum+1) << '\n' ;
    cout << "Enter new tweet :" << endl ;
    getline(cin , newTweetStr) ;

    tweetOfUser[tweetNum].setTweetStr(newTweetStr) ;
}

void User :: increaseLike (string userName ,int tweetNum)
{
    if(tweetOfUser[tweetNum].getLikeSet().find(userName) == tweetOfUser[tweetNum].likeSet.end()) //not find
    {
        tweetOfUser[tweetNum].tweetLikes++ ;
        tweetOfUser[tweetNum].likeSet.insert(userName) ;
    }
    else
    {
        throw  invalid_argument("!You have already liked this") ;
    }
}
string User::print()const
{
    ostringstream outPut ;
    Date D;

    outPut << "\nName: "      << firsName 
           << "\nUsername: "  << userName
           << "\nPassword: "  << password 
           << "\nBiograghy: " << biogarghy
           << "\nCountry: "   << country <<'\n'; 
           //<< "\nage: "       << D.getAge(); //error!

    return outPut.str() ;
}
