#include <iostream>
#include <ctime> 

#include "Date.h"

using namespace std;

void Date :: setDate(string date)
{
    this -> date = date;

}

int   Date :: getAge()
{
    userAge = 2023 - stoi(date.substr(0,4));
    return userAge; 
}

string Date :: getTweetDate()
{
    time_t now = time(0);
    char * dt  = ctime(&now);
     
    return dt;

}