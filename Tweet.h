#include <unordered_set>
#include <string>

#ifndef TWEET_H
#define TWEET_H

class Tweet
{
    public :

        Tweet();
        Tweet(std::string);

        void setTweetStr (std::string);

        std::string getTweetStr ()const;

    private :
        std::string tweetStr ;
        std::unordered_set<std::string> likeSet ; 
};

#endif