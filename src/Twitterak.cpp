#include <cctype>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <unordered_map>

#include "Twitterak.h"
#include "User.h"
#include "Functions.h"

#define  sleepTime  1  // for sleep time

using namespace std;

short int Twitterak::findUser (const vector<string>& words)
{
    short int userIndex {-1} ;

    for(size_t i = 0 ; i < words.size() ; ++i)
        if(words[i][0] == '@')
            userIndex = i ;
    //Cant't optimize with break beacaus : like @user:@user -> wrong command not index 1
    if(userIndex > -1 && words[userIndex] == "@me")
        return -1 ;

    unordered_set <string> commandBeforUser {"like" , "dislike" , "profile"} ;
    //This help in future just add command no need to change more 

    if      (userIndex >   1)
        throw invalid_argument("wrong @ place") ;
    else if (userIndex ==  1 && commandBeforUser.find(words[0]) == commandBeforUser.end())
        throw invalid_argument("wrong @ place") ;
    //avoid logical error on : tweet @user "hhhhhh"   

    if( userIndex > -1 && !usersMap.count(words[userIndex].substr(1))) //hey not done @mmmmm , mmmm
        throw invalid_argument ("user not found") ;

    return userIndex ; /* only -1 , 0 , 1*/
}

string Twitterak::defaultAdd() //add user format name , firsCharOf name + 1234,firsCharOf name
{
    ostringstream outPut;

    User u1 ("mamad","m1234","m");
    usersMap["m1234"] = u1;

    User u2 ("ali"  ,"a1234","a");
    usersMap["a1234"] = u2;

    outPut << "default build : ali , mamad " ;
    return outPut.str() ;
}
void Twitterak::run()
{
    cout << defaultAdd() << "\n\n" ;

    cout << "Wellcom to twitterak \nMade by group of Losers ALL the times (LA)!\nUse help command if you are new!\n";

    bool isGoing = 1;
    string caseOfMenu {""};

    while (isGoing) {
        caseOfMenu = "";
        cout << ">";

        getline(cin, caseOfMenu);
        lowerStr(caseOfMenu);

        vector<string> words = wordSeparator(caseOfMenu);

        unordered_map <string , void(Twitterak::*)(vector<string>) > connectiveMap ;

        connectiveMap["login" ] = &Twitterak::logIn;
        connectiveMap["signup"] = &Twitterak::signUp;
        connectiveMap["help"  ] = &Twitterak::help;

        if(connectiveMap.count(words[0]))
        {
            auto fun = connectiveMap[words[0]] ;
            (this->*fun) (words) ;
        }

        else if (caseOfMenu == "") ;

        else if (caseOfMenu == "exit" || caseOfMenu == "q" || caseOfMenu == "quit")
            isGoing = 0;

        else
            cout << "! Wrong commant! try again....!\n"; // can be done with execption
    }
}
void Twitterak::logIn(vector<string> words)
{
    string tempUserName {}, tempPassword {};

    if (words.size() > 1) 
    {
        tempUserName = words[1];
    } 
    else 
    {
        cout << "$ Username :";
        getline(cin,tempUserName);
    }

    if (words.size() > 2) {
        tempPassword = words[2];
    } 
    else 
    {
        tempPassword = getpass("$ Password :");
    }

    tempUserName = bringImportant(tempUserName, 0); //better to add other function

    if (usersMap.count(tempUserName)) // logic error in last try
    {
        int wrongTrys { 2 };
        for (; usersMap[tempUserName].getPassword() != tempPassword && wrongTrys > 0; wrongTrys--) // is it correct?
        {
            cout << "! Incorect password\n"
                 << wrongTrys << " Try remain :";
            tempPassword = getpass("");
        }

        if (wrongTrys > 0) {
            cout << "* Welcome " << usersMap[tempUserName].getFirstName() << '\n';
            userOptions(tempUserName);
        }
    } else {
        cout << "! User not found!\n";
    }
}
void Twitterak::signUp(vector<string> words)
{
    system("clear");
    string tempName, tempUserName, tempPassword;
    if (words.size() == 2) 
    {
        tempUserName = words[1];
    } 
    else if (words.size() == 1) 
    {
        cout << "$ Username :";
        getline(cin , tempUserName); // carefull about @m1234
    } 
    else 
    {
        cout << "! Invalid input \n";
        return;
    }

    tempUserName = bringImportant(tempUserName, 0);

    if (usersMap.count(tempUserName)) {
        cout << "! Duplicate user name\n";
    } else {
        tempPassword = getpass("$ Password :"); // this can only hide the password
        cout << "$ Name : ";
        getline(cin , tempName);

        try {
            User temp(tempName, tempUserName, tempPassword);
            usersMap[tempUserName] = temp;
            cout << "* Registration successful\n";
            sleep(sleepTime);

            vector<string> words { tempName, tempUserName, tempPassword };
            logIn(words);
        } catch (invalid_argument& err) {
            cout << err.what() << "\n";
        }
    }
    // cin.ignore() ;
}

void Twitterak::help  (vector<string>words)
{
    cout << "login  : For login you have to sign in befor.\n"
         << "signup : If you don't have acount account use this opstion to creat on.\n"
         << "exit   : Close the program.\n";

}

void Twitterak::userOptions(const string& userName)
{
    this->userName = userName ;
    string command;

    unordered_map <string , void(Twitterak::*)(vector<string>) > connectiveMap ;
    connectiveMap["profile"] = & Twitterak::goPrint ;
    connectiveMap["me"]      = & Twitterak::goPrint ;
    connectiveMap["tweet"]   = & Twitterak::goTweet ;


    while (command != "logout") 
    {
        try
        {
            cout << ">@" << userName << '>';

            getline(cin, command);
            lowerStr(command);

            vector<string> words = wordSeparator(command);

            string tempCommand = words[0];

            for(int i = 0 ; i + 1< words.size() && i < 4 ; ++i)
            {
                cout << "command is : " << tempCommand << '\n' ;
                if(connectiveMap.count(words[0]))
                {
                    (this->*connectiveMap[words[0]])(words) ;
                    break ;
                }
                tempCommand += ' ' + words[i+1] ;
            }

            if (words[0] == "help") //help
            {
                //cout << helpLogin();
            }

            else if (words.size() >= 4 && words[0] + " " + words[1] == "edit profile") //edit profile somepart "somethinf  f f"
            {
                    cout << usersMap[userName].changeProfile(words) << '\n';          
            }

            else if (command == "delete account") //delete account
            {
                if (deleteAccount(userName))
                    command = "logout";
            }

            else if (words[0] == "@me" || usersMap.count(bringImportant(command, 0))) // @username
            {
                if ("@me" == words[0])
                {
                    cout << '\n'<< usersMap[userName].getTweet() << '\n';
                }
                else
                {
                    cout << usersMap[bringImportant(command, 0)].getTweet() << '\n';
                }

            } 
            else if (words.size() > 1 && usersMap.count(bringImportant(words[0]))) // @username:number
            {
                cout << '\n' << usersMap[bringImportant(words[0])].getTweet(stoi(words[1]), stoi(words[1]) + 1) << '\n';
            }

            else if (command.substr(0, 13) == "delete tweet ") //delete tweet 4
            {
                usersMap[userName].deleteTweet(bringImportant(command, 13));
            }

            else if (command.substr(0, 11) == "edit tweet ")  // edit tweet 8
            {
                usersMap[userName].editTweet(bringImportant(command, 11));
            }

            else if (words.size() > 2 && words[0] == "retweet") // retweet @rrrrrr:rrr   ****chech user
            {
                usersMap[userName].retweet(usersMap[words[1]], stoi(words[2]));
            } 
            else if (words.size() > 2 && words[0] + " " + words[1] == "quote tweet")  // retweet @rrrrrr:rrr "dddddd"  ****chech user
            {
                for (size_t i = 5; i < words.size(); ++i) //fucking bad*******************
                {
                    words[4] += words[i];
                }
                usersMap[userName].retweet(usersMap[words[2]], stoi(words[3]), words[4]);
            }

            else if (words[0] == "like") // like @user:8
            {
                words[1] = bringImportant(words[1], 0);
                if (words.size() == 3 && usersMap.count(words[1])) 
                {
                    usersMap[words[1]].increaseLike(userName, stoi(words[2]));
                    
                } else {
                    cout << "! Invalid input after like \n";
                }
            }

            else if(words[0] == "dislike")//dislike @username:4 //check user name  
            {
                words[1] = bringImportant(words[1], 0);
                if (words.size() == 3 && usersMap.count(words[1])) 
                {
                    usersMap[words[1]].decreaseLike(userName, stoi(words[2]));
                    
                } else {
                    cout << "! Invalid input after dislike \n";
                }
            }

            else if (words[0] == "logout") 
            {
                system("clear");
                cout << "* Logout succesfully\n";
            }

            else if (words[0] == "exit" ||
                     words[0] == "quit" || 
                     words[0] == "q"      ) 
            {
                exit(0);
            }


            else if (command == "") 
            {
                // empty
            }

            else 
            {
                cout << "! invalid command \n";
            }
        }
        catch(out_of_range &err)
        {
          
            cout << "! Your number is too big\n" ;
        }
        catch (invalid_argument& err)
        {
            cout << err.what() << '\n' ;
        }
    }
}
bool Twitterak::deleteAccount(const string& userName)
{
    string command;
    cout << "? Are you sure ?(type yes) :";
    cin >> command;

    lowerStr(command);
    if (command == "yes") {
        usersMap.erase(userName);
        return 1;
    }

    return 0;
}
void Twitterak::goPrint (vector<string> words)
{
    //implementate validation


    short int indexOfUser { findUser (words) } ;
    string tempUser = indexOfUser == -1 ? userName : words[indexOfUser].substr(1) ;


    bool showPrivate {words.size() < 2} ;
    cout << "new print\n" ;
    cout << usersMap[tempUser].print(showPrivate) << '\n';
}
void Twitterak::goTweet(std::vector<std::string> words)
{
    //implementate validation

    cout << "new Tweet\n" ;
    usersMap[userName].addTweet(vecToStr(words,1));
}