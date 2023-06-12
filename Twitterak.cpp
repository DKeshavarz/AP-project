#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>

#include "Twitterak.h" 
#include "User.h"

using namespace std ;

//nonMember fuctions *************************
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
        if(command[i] != '"' && command[i] != '@')
            important += command[i] ;
    }

    return important ;
}

//member functions    *************************
void Twitterak::run()
{
    cout << "welcom to twitterak \nmade by group of losers\nuse help command if you are new\n" ;
    showMenu() ; 
} 
void Twitterak::showMenu() 
{
    bool isGoing = 1 ;
    string caseOfMenu {""} ;
    while(isGoing)
    {
        caseOfMenu = "" ;
        cout << ">";

        getline(cin,caseOfMenu);
        lowerStr(caseOfMenu) ;

        if     (caseOfMenu.substr(0,6) == "login") //still need work 
            logIn() ;
        else if(caseOfMenu == "signup")
            signUp();
        else if(caseOfMenu == "help")
            cout << help() ;
        else if(caseOfMenu == "")
        {}
        else if(caseOfMenu == "exit" || caseOfMenu == "q" || caseOfMenu == "quit")
            isGoing = 0 ;
        else
            cout << "wrong commant try agane\n" ;  //can be done with execption

    }
}
void Twitterak::logIn(string tempUserName , string tempPassword)
{
    system("clear") ; 

    if(tempUserName.empty())
    {
        cout << "enter yout user name :";
        cin >> tempUserName ;
    }
    if(tempPassword.empty())
    {
        cout << "enter your password : ";
        cin >> tempPassword ; 
    }

    if(usersMap.count(tempUserName))
    {
        int wrongTrys {2} ;
        for( ;usersMap[tempUserName].getPassword() != tempPassword && wrongTrys > 0 ; wrongTrys--)//is it correct?
        {
            cout << "incorect password\n" << wrongTrys << "try remain :";
            cin >> tempPassword ;   
        }
        
        if(wrongTrys > 0 )
        {
            cout << "wellcom " << usersMap[tempUserName].getFirstName() << '\n' ;
            userOptions(tempUserName) ;
        }
    }
    else
    {
        cout << "user not found\n" ;
    }   
}
void Twitterak::signUp () 
{
    system("clear") ;
    string tempName , tempUserName , tempPassword ; 

    cout << "enter your name : "    ;cin >> tempName ;
    cout << "enter yout user name :";cin >> tempUserName ; //carefull about @m1234
    cout << "enter your password : ";cin >> tempPassword ; 
 
    if(usersMap.count(tempUserName))
    {
        cout << "!duplicate user name\n" ; 
    }
    else
    {
        try
        {
            User temp(tempName,tempUserName,tempPassword) ;
            usersMap[tempUserName] = temp;
            cout << "registration successful\n" ;
            logIn(tempUserName,tempPassword) ;
        }
        catch (invalid_argument &err)
        {
            cout << err.what() << "\n" ;
        }
    }
    cin.ignore() ;
}

string Twitterak::help() const
{
    system ("clear") ;

    ostringstream outPut ;
    outPut << "login  : for login you have to sign in befor\n"
           << "signup : if you don't have acount account use this opstion to creat on\n"
           << "exit   : close program\n" ;

    return outPut.str() ;
}
void Twitterak::userOptions (const string& userName) 
{
    string command ;
    cin.ignore() ;
    
    while(command != "logout")
    {
        cout << userName << '>' ;

        getline(cin , command) ;
        lowerStr(command) ;

        if(command.substr(0,7) == "profile" || command == "me")
        {   
            if(command.size() > 7)
                cout << usersMap[bringImportant(command , 8)].print() << '\n';
            else
                cout << usersMap[userName].print() << '\n' ;  
        }
        else if(command == "delete account")
        {
            if(deleteAccount(userName))
                command = "logout";
        }
        else if(command.substr(0,6) == "tweet ")
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
        else if(command.substr(0,5) == "like ")
        {
            //if( usersMap.count( command.substr(,4) ) )
        }
        else if(command == "logout")
        {
            //empty
        }
        else if(command == "") 
        {
            //empty
        }
        else
        {
            cout << "invalid command \n" ;
        }
        
    }  
}
bool Twitterak::deleteAccount(const string& userName) 
{
    string command ;
    cout << "are you sure ?(type yes) :" ;
    cin >> command ;

    lowerStr(command) ;
    if(command == "yes")
    {
        usersMap.erase(userName) ;
        return 1;
    }

    return 0 ;
}

