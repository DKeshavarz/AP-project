// tuple
// "\n\n" and '\n\n'
// software architect 
//progit

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <unistd.h>

#include "Twitterak.h" 
#include "User.h"

using namespace std ;

const int n = 1 ; // for sleep time
//nonMember fuctions *************************
vector <string> wordSeparator(string command)
{
    vector <string> words;
    string tempCommand;

    for (size_t i = 0 ; i < command.size() ; ++i)
    {
        if (command[i] != ' ' && command[i] != ':') //confutoin
        {
            tempCommand  += command[i]; 
        }

        else if (tempCommand != "")
        {
            words.push_back(tempCommand);
            tempCommand = "" ;
        }
    }

    if (tempCommand.size() > 0 && command[command.size() - 1] != ' ')
    {
        words.push_back(tempCommand);
    }
    else
    {
        words.push_back(" ") ;
    }

    // cout << "in..\n" ;
    // for(auto i : words)
    //     cout << i << ".." ;
    // cout << "out..\n" ;
    
    return words;
}
void lowerStr(string &str)
{
    for(char& i : str)
        i = tolower(i) ;
} 
string bringImportant(const string& command, size_t start ) //sugest to pass argument for delete
{
    string important {} ;

    for(size_t i = start ; i < command.size() ; ++i)
    {
        if(command[i] != '"'  && command[i] != '@')
            important += command[i] ;
    }

    return important ;
}

//member functions    *************************
void Twitterak::run()
{

    cout << "Wellcom to twitterak \nMade by group of LOSERS!\nUse help command if you are new!\n" ;

    bool isGoing = 1 ;
    string caseOfMenu {""} ;
    while(isGoing)
    {
        caseOfMenu = "" ;
        cout << ">";

        getline(cin,caseOfMenu);
        lowerStr(caseOfMenu) ;

        vector <string> words = wordSeparator(caseOfMenu);
        if     (words[0] == "login") //still need work 
            logIn (words) ;

        else if(words[0] == "signup")
            signUp(words) ;

        else if(caseOfMenu == "help")
            cout << help() ;

        else if(caseOfMenu == "")
        {}

        else if(caseOfMenu == "exit" || caseOfMenu == "q" || caseOfMenu == "quit")
            isGoing = 0 ;

        else
            cout << "! Wrong commant! try again....!\n" ;  //can be done with execption

    }
}
void Twitterak::logIn(vector<string>words)
{
    string tempUserName{} , tempPassword{};

    system("clear") ; 

    if(words.size() > 1)
    {
        tempUserName= words[1];
    }
    else
    {
        cout << "$ Username :";
        cin  >> tempUserName ;
    }
    
    if(words.size() > 2)
    {
        tempPassword = words[2];
    }
    else
    {
        tempPassword = getpass("$ Password :") ; //this can only hide the password
    }
    
    tempUserName = bringImportant(tempUserName,0) ;

    if(usersMap.count(tempUserName)) // logic error in last try
    {
        int wrongTrys {2} ;
        for( ;usersMap[tempUserName].getPassword() != tempPassword && wrongTrys > 0 ; wrongTrys--)//is it correct?
        {
            cout << "! Incorect password\n" << wrongTrys << " Try remain :" ;
            tempPassword = getpass("") ;
        }
        
        if(wrongTrys > 0 )
        {
            cout << "* Welcome " << usersMap[tempUserName].getFirstName() << '\n' ;
            userOptions(tempUserName) ;
        }
    }
    else
    {
        cout << "! User not found!\n" ;
    }   
}
void Twitterak::signUp (vector<string>words) 
{
    system("clear") ;
    string tempName , tempUserName , tempPassword ; 
    if(words.size() == 2)
    {
        tempUserName = words[1] ;
    }
    else if (words.size() == 1)
    {
        cout << "$ Username :" ;cin >> tempUserName ; //carefull about @m1234
    }
    else 
    {
        cout << "! Invalid input \n" ;
        return ;
    }

    tempUserName = bringImportant(tempUserName,0) ;

    if(usersMap.count(tempUserName))
    {
        cout << "! Duplicate user name\n" ; 
    }
    else
    {
        tempPassword = getpass("$ Password :")  ; //this can only hide the password
        cout << "$ Name : "    ;cin >> tempName ;

        try
        {
            User temp(tempName,tempUserName,tempPassword) ;
            usersMap[tempUserName] = temp;
            cout << "* Registration successful\n" ;
            sleep(n);
            
            vector <string> words {tempName,tempUserName,tempPassword};
            logIn(words) ;
        }
        catch (invalid_argument &err)
        {
            cout << err.what() << "\n" ;
        }
    }
    //cin.ignore() ;
}

string Twitterak::help() const
{
    system ("clear") ;

    ostringstream outPut ;
    outPut << "login  : For login you have to sign in befor.\n"
           << "signup : If you don't have acount account use this opstion to creat on.\n"
           << "exit   : Close the program.\n" ;

    return outPut.str() ; // I dont understand why use .str()?
}
void Twitterak::userOptions (const string& userName) 
{
    string command ;
    cin.ignore() ;
    
    while(command != "logout")
    {

        cout << ">@" << userName << '>' ;

        getline(cin , command) ;
        lowerStr(command) ;
        
        vector <string> words = wordSeparator(command);

        if(words[0]== "profile" || words[0] == "me" || words[0] == "@me")
        {   
            if(command.size() > 7)
            {
                cout << usersMap[bringImportant(command , 8)].print() << '\n';
            }
            else
            {
                cout << usersMap[userName].print() << '\n' ;
            }  
        }

        else if(command == "delete account")
        {
            if(deleteAccount(userName))
                command = "logout";
        }

        else if(words[0] == "tweet")
        {
            usersMap[userName].addTweet( bringImportant(command,6) ) ;
        }

        else if(usersMap.count(bringImportant(command,0)))
        {
            cout << usersMap[bringImportant(command,0)].getTweet() << '\n' ;
        }

        else if(command.substr(0,13) == "delete tweet ")
        {
            usersMap[userName].deleteTweet(bringImportant(command,13)) ;
        }

        else if(command.substr(0,11) == "edit tweet ")
        {
            usersMap[userName].editTweet(bringImportant(command,11)) ;
        }

        else if(words[0] == "like")
        {
            words[1] = bringImportant(words[1],0) ;
            if(words.size() == 3 && usersMap.count(words[1]))
            {
                try
                {

                    usersMap[words[1]].increaseLike(userName,stoi(words[2])) ;
                }
                catch (invalid_argument &err)
                {
                    cout << err.what() << '\n';
                }
            }
            else
            {
                cout << "! Invalid input after like \n" ;
            }
        }

        else if(words[0] == "logout")
        {
            system("clear");
            cout << "* Logout succesfully"; // we most push enter to that line get the other line!
        }
        else if (words[0] == "exit" || // i add this to user can exit without logging out.
                 words[0] == "quit" || 
                 words[0] == "q")
        {
            exit(0);
        }

        else if(command == "") 
        {
            //empty
        }

        else
        {
            cout << "! invalid command \n" ;
        }
        
    }  
}
bool Twitterak::deleteAccount(const string& userName) 
{
    string command ;
    cout << "? Are you sure ?(type yes) :" ;
    cin >> command ;

    lowerStr(command) ;
    if(command == "yes")
    {
        usersMap.erase(userName) ;
        return 1;
    }

    return 0 ;
}