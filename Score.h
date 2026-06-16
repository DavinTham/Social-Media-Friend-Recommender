#ifndef SCORE_H
#define SCORE_H
#include "User.h"
#include <string>
#include <vector>
using namespace std;

class Score {
public:
    // count how many interests two users share
    static int countSharedInterests(const User& user1, const User& user2);

    // count profile similarities
    static int sameLocationScore(const User& user1, const User& user2);

    // calculate final recommendation score
    static int calculateScore(const User& user1, const User& user2);
};

#endif