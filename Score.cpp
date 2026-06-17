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
    if (user1.getLocation() == user2.getLocation() && !user1.getLocation().empty()) {
        return 4;
    }

    return 0;
}

int Score::sameSchoolScore(const User &user1, const User &user2) {
    if (user1.getSchool() == user2.getSchool() && !user1.getSchool().empty()) {
        return 3;
    }
    return 0;
}

int Score::sameMajorScore(const User &user1, const User &user2)
{
    if (user1.getMajor() == user2.getMajor() && !user1.getMajor().empty())
    {
        return 2;
    }
    return 0;
}

int Score::sameAgeScore(const User &user1, const User &user2)
{
    if (user1.getAge() == user2.getAge())
    {
        return 1;
    }
    return 0;
}

int Score::calculateScore(int mutualFriends, const User &user1, const User &user2) {
    int sharedInterests = countSharedInterests(user1, user2);
    int sameLocation = sameLocationScore(user1, user2);
    int sameAge = sameAgeScore(user1, user2);
    int sameMajor = sameMajorScore(user1, user2);
    int sameSchool = sameSchoolScore(user1, user2);

    int score = 0;

    // project formula:
    score = (5 * mutualFriends) + (2 * sharedInterests) + sameLocation + sameSchool + sameMajor + sameAge;

    return score;
}


