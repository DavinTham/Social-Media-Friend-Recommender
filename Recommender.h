#ifndef RECOMMENDER_H
#define RECOMMENDER_H
#include "user.h"
#include "Graph.h"
#include "Score.h"
#include <unordered_map>
#include <vector>
#include <utility>
using namespace std;

class Recommender {
    private:
    unordered_map<int, User> users;
    Graph graph;

    public:
    // add user
    void addUser(const User& user);

    // add mutual
    void addFriendship(int userID1, int userID2);

    // add user interest
    void addUserInterest(int userID, const string &interest);

    // check if user exists
    bool hasUser(int userID) const;

    //get recommendation as pair (userID & score)
    vector<pair<int, int> > recommendFriends(int userID);

    //get recommendation for users with no friends (cold start)
    vector<pair<int, int> > coldStartRecommendations(int userID);

    //print recommendations
    void displayRecommendations(int userID);

    //BFS distance using graph
    void displayBFSDistance(int userID, int maxDepth);

    //stress test
    void stressTest(int numberOfUsers);
};

#endif
