#ifndef SOCIAL_MEDIA_FRIEND_RECOMMENDER_H
#define SOCIAL_MEDIA_FRIEND_RECOMMENDER_H

#include <iostream>
#include "User.h"

using namespace std;

int main () {
    // set user info
    User alice(1, "Davin", 20, "Seattle");
    alice.addInterest("gaming");

    // print user info
    alice.display();

    return 0;
}

#endif 