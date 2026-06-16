#include "recommender.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Recommender::addUser(const User& user) {
    users[user.getID()] = user;
    graph.addUser(user.getID());
}

void Recommender::addFriendship(int userID1, int userID2) {
    if (!hasUser(userID1) || !hasUser(userID2)) {
        cout << "One or both users do not exist." << endl;
        return;
    }

    graph.addFriend(userID1, userID2);
}

bool Recommender::hasUser(int userID) const{
    return users.find(userID) != users.end();
}

vector<pair<int,int>> Recommender::recommendFriends(int userID) {
    vector<pair<int,int>> recommendations;

    if (!hasUser(userID)) {
        return recommendations;
    }

    unordered_set<int> directFriends = graph.getNeighbors(userID);

    //cold start
    if (directFriends.empty()) {
        return coldStartRecommendations(userID);
    }

    unordered_set<int> candidates;

    // mutual algorithm
    for (int friendID : directFriends) {
        unordered_set<int> friendsOfFriend = graph.getNeighbors(friendID);

        for (int candidateID : friendsOfFriend) {

            //remove self
            if (candidateID == userID) {
                continue;
            }

            //remove existing frineds
            if (directFriends.find(candidateID) != directFriends.end()) {
                continue;
            }

            candidates.insert(candidateID);
        }
    }

    //calculate each candiddate score
    for (int candidateID : candidates) {
        int mutualFriends = (int)graph.getMutualFriends(userID, candidateID).size();

        int finalScore = Score::calculateScore(
            mutualFriends,
            users[userID],
            users[candidateID]
            );

        recommendations.push_back({candidateID, finalScore});
    }

    //sort highest score
    sort(recommendations.begin(), recommendations.end()
        [](pair<int,int> a, pair<int,int> b) {
            return a.second > b.second;
        });

    return recommendations;
}

vector<pair<int,int>> Recommender::coldStartRecommendations(int userID) {
    vector<pair<int,int>> recommendations;

    if (!hasUser(userID)) {
        return recommendations;
    }

    User targetUser = users[userID];

    for (auto pair : users) {
        int otherID = pair.first;
        User otherUser = pair.second;

        //dont recommend urself
        if (otherID == userID) {
            continue;
        }

        //no mutual (cold start)
        int mutualFriends = 0;

        int finalScore = Score::calculateScore(
            mutualFriends,
            targetUser,
            otherUser
            );

        //add extra profile matching (cold start)
        if (targetUser.getSchool() == otherUser.getSchool()) {
            finalScore +== 2;
        }

        if (targetUser.getMajor() == otherUser.getMajor()) {
            finalScore +== 2;
        }

        if (targetUser.getLocation() == otherUser.getLocation()) {
            finalScore +== 2;
        }

        if (targetUser.getInterests() == otherUser.getInterests()) {
            finalScore +== 2;
        }

        if (targetUser.getAge() == otherUser.getAge()) {
            finalScore +== 2;
        }

        if (finalScore > 0) {
            recommendations.push_back({userID, finalScore});
        }
    }

    sort(recommendations.begin(), recommendations.end(), [](pair<int,int> a, pair<int,int> b) {
        return a.second > b.second;
    });

    return recommendations;
}

void Recommender::displayRecommendations(int userID) {
    if (!hasUser(userID)) {
        cout << "User not found." << endl;
        return;
    }

    vector<pair<int,int>> recommendations = recommendFriends(userID);

    cout << endl;
    cout << "Friend recommendations for " << users[userID].getName() << ":" << endl;

    if (recommendations.empty()) {
        cout << "No recommendation found." << endl;
        return;
    }

    for (pair<int,int> recommendation : recommendations) {
        int recommendedID = recommendation.first;
        int score = recommendation.second;

        int mutualFriends = (int)graph.getMutualFriends(userID, recommendedID).size();
        int sharedInterests = Score::countSharedInterests(users[userID], users[recommendedID]);

        cout << "- " << users[recommendID].getName();
        cout << " | Score: " << score;
        cout << " | Mutual friends: " << mutualFriends;
        cout << " | SharedInterests: " << sharedInterests;
        cout << " | Location: " << users[recommendedID].getLocation();
        cout << endl;
    }
}

void Recommender::displayBFSDistance(int userID, int maxDepth) {
    if (!hasUser(userID)) {
        cout << "User not found." << endl;
        return;
    }

    unordered_map<int, int> distances = graph.BFS(userID, maxDepth);

    cout << endl;
    cout << "BFS distance from " << users[userID].getName() << ":" << endl;

    for (auto pair : distances) {
        int otherID = pair.first;
        int distance = pair.second;

        cout << users[userID].getName() << " is ";
        cout << distance << " friendship miles away" << endl;
    }
}

void Recommender::stressTest(int numberOfUsers) {
    cout << endl;
    cout << "Stress test started with " << numberOfUsers << " users." << endl;

    for (int i = 1000; i < 1000 + numberOfUsers; i++) {
        User tempUser(i, "TestUser" + to_string(i), 20, "Test School", "Test Major", "Test City");
        tempUser.addInterest("testing");
        addUser(tempUser);
    }

    for (int i = 1000; i < 999 + numberOfUsers; i++) {
        addFriendship(i, i + 1);
    }

    cout << "Stress test completed successfully." << endl;
    cout << "Total users in graph: " << graph.userCount() << endl;
}
