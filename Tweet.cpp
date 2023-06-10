
#include "Tweet.h"

using namespace std ;

Tweet::Tweet()
{}
Tweet::Tweet(string inputTweetStr)
{
    tweetStr = inputTweetStr ;
}

void Tweet::setTweetStr (string input)
{
    tweetStr = input ;
}

string Tweet::getTweetStr ()const
{
    return tweetStr ;
}