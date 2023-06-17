#include <iostream>
#include <ctime> 
#include <stdexcept>
#include <vector>

#include "Date.h"

using namespace std;
vector <string> wordSeparator(string) ;

Date::Date () 
{
    //empty
}
Date::Date (string inputDate)
{
    setDate(inputDate) ;
}
void Date::setDate(string inputDate) //17 02 2023
{
    vector <string> words = wordSeparator(inputDate) ;
    if(words.size() == 3)
    {
        day   = stoi(words[0]) ;
        month = stoi(words[1]) ;
        year  = stoi(words[2]) ;

        if(!(year <=2023 && 1 <= month && month <= 12 && 1 <= day && day <= 30 + (month > 6)))
            throw invalid_argument("invlaid date") ;

    }
    else
        throw invalid_argument ("invalid date prototype") ;

    setAge() ;

}

void  Date :: setAge()
{
    userAge = 2023 - year ; 
}

string Date :: getTweetDate()
{
    time_t now = time(0);
    char * dt  = ctime(&now);
     
    return dt;

}