#include <iostream>
#include <ctime> // used to work with date and time
#include <chrono>

#include "Date.h"

using namespace std;

void Date :: setDate(string date)
{
    this -> date = date;
}

int  Date ::getAge()
{
    userAge = 2023 - stoi(date.substr(0,4));
    return userAge; 
}

auto getTweetDate()
{
    auto givemetime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    return &givemetime;
}