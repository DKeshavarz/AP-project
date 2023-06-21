#include <vector>
#include <string>
#include <iostream>

#include "Functions.h"

using namespace std ;

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

string vecToStr (vector<string>words, size_t start)
{
    string temp;
    for(size_t i = start ; i < words.size() ; ++i)
    {
        temp += words[i] ;
        if(i+1 < words.size())
            temp+= ' ' ;
    }

    return temp ;
}