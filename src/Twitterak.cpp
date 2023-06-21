// tuple
// "\n\n" and '\n\n'
// software architect
// progit

// zibasazi notweet yet
// fix @usernames in useroptions

#include <cctype>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <vector>

#include "Twitterak.h"
#include "User.h"
#include "Functions.h"

#define  sleepTime  1  // for sleep time

using namespace std;


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

        if (words[0] == "login") // still need work
            logIn(words);

        else if (words[0] == "signup")
            signUp(words);

        else if (caseOfMenu == "help")
            cout << help();

        else if (caseOfMenu == "") {
        }

        else if (caseOfMenu == "exit" || caseOfMenu == "q" || caseOfMenu == "quit")
            isGoing = 0;

        else
            cout << "! Wrong commant! try again....!\n"; // can be done with execption
    }
}
void Twitterak::logIn(vector<string> words)
{
    string tempUserName {}, tempPassword {};

    system("clear");

    if (words.size() > 1) {
        tempUserName = words[1];
    } else {
        cout << "$ Username :";
        cin >> tempUserName;
    }

    if (words.size() > 2) {
        tempPassword = words[2];
    } 
    else 
    {
        tempPassword = getpass("$ Password :"); // this can only hide the password
    }

    tempUserName = bringImportant(tempUserName, 0);

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
    if (words.size() == 2) {
        tempUserName = words[1];
    } else if (words.size() == 1) {
        cout << "$ Username :";
        cin >> tempUserName; // carefull about @m1234
    } else {
        cout << "! Invalid input \n";
        return;
    }

    tempUserName = bringImportant(tempUserName, 0);

    if (usersMap.count(tempUserName)) {
        cout << "! Duplicate user name\n";
    } else {
        tempPassword = getpass("$ Password :"); // this can only hide the password
        cout << "$ Name : ";
        cin >> tempName;

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

string Twitterak::help() const
{
    system("clear");

    ostringstream outPut;
    outPut << "login  : For login you have to sign in befor.\n"
           << "signup : If you don't have acount account use this opstion to creat on.\n"
           << "exit   : Close the program.\n";

    return outPut.str();
}

string Twitterak::helpLogin() const
{
    system("clear");
    ostringstream outPut;
    outPut
        << "profile or me                        : For see your account details.\n"
        << "edit profile                         : For edit your account details , like this -> edit profile birthdate 2000 12 12.\n"
        << "delete account                       : If you want to delete your account(yes please do that!).\n"
        << "tweet                                : When you want to add a tweet , like this -> tweet Hey ya loser! welcome to LA!\n"
        << "@me or your username                 : If you want to see your tweets.\n"
        << "another person username              : If you want to see tweet of another users.\n"
        << "username:a number                    : If you want to see one of your tweets or another users tweets (number most be a number!).\n\n"
        << "delete tweet number of that tweet    : If you want to delet that tweet(yes please delete all your bullshit tweets).\n"
        << "edit tweet number of that tweet      : If you want to edit that tweet!\n"
        << "retweet username:number              : When you want retweet another user tweet!\n"
        << "quote tweet username:number add tweet: Exactly like retweet, but you add a tweet after number.\n"
        << "like username:number of tweet        : If you want to like that tweet(please do not do that, just dislike bullshit tweets).\n"
        << "dislike username:number of tweet     : If you want to dislike that tweet ,note that you most already liked that tweet before.\n"
        << "logout                               : For logging out your account.\n"
        << "exit or quit or q                    : For close the program.\n";

    return outPut.str();
}

void Twitterak::userOptions(string& userName)
{
    string command;
    cin.ignore();

    while (command != "logout") 
    {
        try
        {
            cout << ">@" << userName << '>';

            getline(cin, command);
            lowerStr(command);

            vector<string> words = wordSeparator(command);

            if (words[0] == "profile" || words[0] == "me")  //profile "mabyuser name"
            {
                if (command.size() > 7) 
                {
                    cout << usersMap[bringImportant(command, 8)].print(0) << '\n';
                } 
                else 
                {
                    cout << usersMap[userName].print(1) << '\n';
                }
            }

            else if(words.size() >= 4 && words[0]+ " " +words[1]+ " " + words[2] == "edit profile username")
            {
                string tempUserName = vecToStr(words , 3);
                bringImportant(tempUserName) ;

                if(usersMap.count(tempUserName))
                {
                    cout << "duplicated user name can't change \n" ;
                }
                else
                {
                    usersMap[userName].setUserName(tempUserName) ;
                    usersMap[tempUserName] = usersMap[userName];
                    usersMap.erase(userName) ;
                    userName = tempUserName ;

                }
            }

            else if (words[0] == "help") //help
            {
                cout << helpLogin();
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

            else if (words[0] == "tweet") //tweet 7 
            {
                usersMap[userName].addTweet(bringImportant(command, 6));
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