#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Date.h"

using namespace std;
vector<string> wordSeparator(string);

Date::Date()
{
    // empty
}
Date::Date(string inputDate)
{
    setDate(inputDate);
}
void Date::setDate(string inputDate) // 2023 02 17
{
    vector<string> words = wordSeparator(inputDate);

    if (words.size() == 4) {
        year = stoi(words[0]);
        month = stoi(words[1]);
        day = stoi(words[2]);

        if (!(year <= 2023 && 1 <= month && month <= 12 && 1 <= day && day <= 30 + (month > 6)))
            throw invalid_argument("! Invlaid date");

    } else
        throw invalid_argument("! Invalid date prototype");

    setAge();
}

void Date ::setAge()
{
    userAge = 2023 - year;
}
int Date ::getAge() const
{
    return userAge;
}

string Date ::getTweetDate()
{
    time_t now = time(0);
    char* dt = ctime(&now);

    return dt;
}