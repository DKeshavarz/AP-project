#include <iostream>

#include "Tweet.h"
#include "Date.h"

using namespace std ;

Tweet::Tweet()
{}
Tweet::Tweet(string inputTweetStr )
{
    Date D;
    tweetStr = inputTweetStr +"\n\t"+D.getTweetDate();
}

void Tweet::setTweetStr (string input)
{
    Date D; 
    tweetStr = input +"\n\t"+D.getTweetDate();
}

string Tweet::getTweetStr ()const
{
    return tweetStr ;
}