#include <iostream>

#include "Date.h"
#include "Functions.h"

#include "Tweet.h"

using namespace std;

Tweet::Tweet()
{
}
Tweet::Tweet(string inputTweetStr)
{
    Date D;
    tweetStr = inputTweetStr + "\n\n" + D.getTweetDate();
}

void Tweet::setTweetStr(string input)
{
    Date D;
    tweetStr = input + "\n\n" + D.getTweetDate();
}

string Tweet::getTweetStr() const
{
    return tweetStr;
}