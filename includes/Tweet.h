#include <string>
#include <unordered_set>
#include <vector>

#ifndef TWEET_H
#define TWEET_H

class User;

class Tweet {
    friend class User;

public:
    Tweet();
    Tweet(std::string);

    void setTweetStr(std::string);

    std::string getTweetStr() const;
    std::unordered_set<std::string> getLikeSet() const { return likeSet; }

private:
    std::unordered_set<std::string> likeSet;
    std::string tweetStr;
    std::vector<Tweet*> mentions;

    int tweetLikes {};
};

#endif