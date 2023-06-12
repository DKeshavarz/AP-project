#include <unordered_set>
#include <string>
#include <vector>

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
        std::vector<Tweet *>mentions ;

        int likes {} ;
};

#endif