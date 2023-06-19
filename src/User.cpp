#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Date.h"
#include "Functions.h"
#include "Tweet.h"
#include "Twitterak.h"
#include "User.h"

using namespace std;

vector<string> wordSeparator(string);
string bringImportant(const string&, size_t);

User::User()
{
}
User::User(string firsName, string userName, string password)
    : tweetNumber { 1 }
{
    setFirsrName(firsName);
    setUserName(userName);
    setPassword(password);
}
void User::setFirsrName(string fName)
{
    firsName = fName;
}
void User::setUserName(string Uname)
{

    if (Uname.size() < 5)
        throw invalid_argument("! Username is to short");
    else if ('0' <= Uname[0] && Uname[0] <= '9')
        throw invalid_argument("! Username shouldn't start with numbers");

    for (size_t i = 1; i < Uname.size(); ++i) {
        if (!('0' <= Uname[i] && Uname[i] <= '9') && !('a' <= Uname[i] && Uname[i] <= 'z') && !('A' <= Uname[i] && Uname[i] <= 'Z')) {
            throw invalid_argument("! Username contain invalic character");
        }
    }

    string reservedWord { "exit,help,login,edit,signup,logout,profile" }; // it may contion more...//i add some

    if (reservedWord.find(Uname) != string::npos)
        throw invalid_argument("! Username is a command!!");

    userName = Uname;
}
void User::setLink(string inputLink)
{
    if (inputLink.find("https://") == string :: npos)
    {
        link = "https://" + inputLink;
    }
    else
    {
        link = inputLink;
    }

}
void User::setPassword(string pas)
{
    // rate password
    password = pas;
}
void User::setBiogarghy(string bio)
{
    if (bio.size() < 160)
        biogarghy = bio;
    else
        throw invalid_argument("! Len of biograghy is too long...");
}
void User::setCountry(string country)
{
    this->country = country;
}
void User::setPhoneNum(string phone) // dose it need validation?
{
    phoneNumber = phone;
}
void User::setBirthDate(string inputString)
{
    birthDate.setDate(inputString);
}

void User::setHeaderColor(string inputColor)
{
    string reservedColors {"blue,green,red,yellow,black,white,orange,purple"};
    if (reservedColors.find(inputColor) != string :: npos)
    {
        throw invalid_argument ("! Your color does not exist");
    }
    headerColor = inputColor;

}

void User::addTweet(string inputTweetStr)
{
    Tweet inputTweet(inputTweetStr);
    tweetOfUser[tweetNumber] = inputTweet;
    tweetNumber++;
}
string User::getFirstName() const
{
    return firsName;
}
string User::getUserName() const
{
    return userName;
}
string User::getLink() const
{
    return link;
}
string User::getPassword() const
{
    return password;
}
string User::getBiogarghy() const
{
    return biogarghy;
}
string User::getCountry() const
{
    return country;
}
string User::getHeaderColor() const
{
    return headerColor;
}
string User::getPhoneNum() const
{
    return phoneNumber;
}
string User::getTweet(size_t start, size_t end)
{
    end = end == 0 ? tweetNumber : end;
    checkTweetExist(end-1) ;

    ostringstream outPut;
    for (size_t i = start; i < end; ++i) {
        if (tweetOfUser.count(i))
            outPut << i << ") " << tweetOfUser[i].getTweetStr() << "\t\t\t\t"
                   << "Likes: " << tweetOfUser[i].tweetLikes << '\n';
    }

    if (outPut.str().empty())
        outPut << "! No tweet yet :) ";

    return outPut.str();
}
void User::checkTweetExist(size_t input) 
{
    if(input >= tweetNumber)
    {
        throw out_of_range("! This tweet doesn't exist") ;
    }
}
void User::deleteTweet(string tweetNumStr)
{
    size_t tweetNum = stoi(tweetNumStr);
    checkTweetExist(tweetNum-1) ;
    tweetOfUser.erase(tweetNum);
}
void User::editTweet(string tweetNumStr) // dose tweet exist ? fucntion has cout ??????
{
    if (birthDate.getAge() < 18) {
        cout << "! your under 18 years old\n";
        return;
    }
    size_t tweetNum = stoi(tweetNumStr);
    string newTweetStr {};

    checkTweetExist(tweetNum) ;

    cout << getTweet(tweetNum, tweetNum + 1) << '\n'; 
    cout << "Enter new tweet :" << endl;
    getline(cin, newTweetStr);

    tweetOfUser[tweetNum].setTweetStr(newTweetStr);
}

void User ::increaseLike(string userName, int tweetNum)
{
    checkTweetExist(tweetNum) ;
    if (tweetOfUser[tweetNum].getLikeSet().find(userName) == tweetOfUser[tweetNum].likeSet.end()) // not find
    {
        tweetOfUser[tweetNum].tweetLikes++;
        tweetOfUser[tweetNum].likeSet.insert(userName);
    } 
    else
    {
        throw invalid_argument("!You have already liked this");
    }
}
void User::decreaseLike(string userName,size_t tweetNum)
{
    checkTweetExist(tweetNum) ;
    if ( tweetOfUser[tweetNum].getLikeSet().find(userName) != tweetOfUser[tweetNum].likeSet.end()) // if find == true
    {
        tweetOfUser[tweetNum].tweetLikes--;
        tweetOfUser[tweetNum].likeSet.erase(userName); 
    } 
    else
    {
        throw invalid_argument("!You have already disliked this");
    }
}
string User ::changeProfile(vector<string>& words) // birth day or birthday ??
{
    string input;
    for (size_t i = 3; i < words.size(); ++i)
        input += words[i] + ' ';

    words[3] = bringImportant(input, 0);
    ostringstream outPut;

    if      (words[2] == "name"       )setFirsrName     (words[3]);
    else if (words[2] == "password"   )setPassword      (words[3]);
    else if (words[2] == "link"       )setLink          (words[3]);
    else if (words[2] == "biography"  )setBiogarghy     (words[3]);
    else if (words[2] == "country"    )setCountry       (words[3]);
    else if (words[2] == "phonenumber")setPhoneNum      (words[3]);
    else if (words[2] == "birthdate"  )birthDate.setDate(words[3]);
    else if (words[2] == "username"   ); // complet me ***********;
    else if (words[2] == "headercolor")setHeaderColor   (words[3]);
    else 
    {
        outPut << "! This part dosen't exist";
        return outPut.str();
    }

    outPut << "* Your " << words[2] << " has been successfully change";
    return outPut.str();
}

void User ::retweet(User userInput, size_t tweetNumInput, string tweetAdd)
{
    checkTweetExist(tweetNumInput) ;
    string str = '@' + userInput.getUserName() + ": " + userInput.getTweet(tweetNumInput, tweetNumInput + 1) + '\n' + tweetAdd;
    addTweet(str);
}
string User::print(bool showPrivate) const
{
    ostringstream outPut;

    outPut << "\nHeadercolor: " << headerColor;
    if (showPrivate) {
        outPut << "\n\nPassword: " << password;
    }
    outPut << "\nName: " << firsName
           << "\nUsername: " << userName
           << "\nLink: " << link
           << "\nBiography: " << biogarghy
           << "\nCountry: " << country
           << "\nage: " << birthDate.getAge() << '\n'; // error!
    return outPut.str();
}

