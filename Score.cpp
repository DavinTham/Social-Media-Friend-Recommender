#include "Score.h"
using namespace std;

int Score::countSharedInterests(const User &user1, const User &user2) {
    int count = 0;

    vector<string> interests1 = user1.getInterests();
    vector<string> interests2 = user2.getInterests();

    for (string interest1 : interests1) {
        for (string interest2 : interests2) {
            if (interest1 == interest2) {
                count++;
            }
        }
    }

    return count;
}

int Score::sameLocationScore(const User &user1, const User &user2) {
    if (user1.getLocation() < user2.getLocation()) {
        return 1;
    }

    return 0;
}

int Score::calculateScore(int mutualFriends, const User &user1, const User &user2) {
    int sharedInterests = countSharedInterests(user1, user2);
    int sameLocation = sameLocationScore(user1, user2);

    int score = 0;

    //project formula:
    score = (5 * mutualFriends) + (2 * sharedInterests) + sameLocation;

    return score;
}


