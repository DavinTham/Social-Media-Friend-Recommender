#ifndef SOCIAL_MEDIA_FRIEND_RECOMMENDER_H
#define SOCIAL_MEDIA_FRIEND_RECOMMENDER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "user.h"
#include "Recommender.h"
#include "Score.h"
#include "Graph.h"

using namespace std;

int main () {
    Recommender recommender;

    // set user info
    User davin(1, "davin", 18, "BC", "ECE", "Bellevue");
    User keiko(2, "keiko", 19, "BC", "CS", "Seattle");
    User samuel(3, "samuel", 19, "BC", "CS", "Seattle"); // similar to keiko
    User coldstart(4, "new", 18, "BC", "ECE", "Bellevue"); // similar to davin

    davin.addInterest("gaming");
    keiko.addInterest("coding");
    samuel.addInterest("coding");
    coldstart.addInterest("gaming");

    /* 
    // 1. testing score
    */
    cout << "\n TESTING SCORE" << endl;

    double lowScore = Score::calculateScore(0, davin, keiko);
    double highScore = Score::calculateScore(0, keiko, samuel); // Should be high

    cout << "davin & keiko similarity score: " << lowScore << endl;
    cout << "keiko & samuel similarity score: " << highScore << endl;

    if (highScore > lowScore)
    {
        cout << "SCORING LOGIC SUCCESS" << endl;
    }
    else
    {
        cout << "=> SCORING LOGIC FAILURE" << endl;
    }

    // add vertices(users)
    recommender.addUser(davin); 
    recommender.addUser(keiko); 
    recommender.addUser(samuel); 
    recommender.addUser(coldstart);

    // add edges(friends)
    recommender.addFriendship(1, 2); // davin (1) <-> keiko (2)
    recommender.addFriendship(2, 3); // keiko (2) <-> samuel (3)

    /*
    // 2. testing recommender
    */
   
    // recommender algorithm
    cout << "\n TESTING RECOMMENDER" << endl;
    recommender.displayRecommendations(1); // davin -> should recommend samuel because he is a friend of keiko(davin's friend)

    // cold start algorithm
    cout << "\n TESTING COLD START ALGORITHM" << endl;
    recommender.displayRecommendations(4); // new user should suggest davin due to matching school, major, and interest.

    // BFS distance algorithm
    cout << "\n TESTING BFS HOPS AND ADJACENCY MATRIX" << endl;
    recommender.displayBFSDistance(1, -1); // shows friendship distance

    // scale testing
    cout << "\n TESTING SYSTEM LOAD CAPACITY" << endl;
    recommender.stressTest(15); // generates 15 artificial users and threads them together linearly to confirm data structure scaling

    cout << "\n TEST COMPLETE" << endl;

    return 0;
}

#endif 