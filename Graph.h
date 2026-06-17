#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Graph {
private:
    // each user id maps to the set of ids they are friends with
    unordered_map<int, unordered_set<int> > adjacency;

public:
    void addUser(int id);
    void addFriend(int a, int b);
    bool hasUser(int id) const;

    unordered_set<int> getNeighbors(int id) const;
    unordered_set<int> getMutualFriends(int a, int b) const;

    // distance in friendship hops from start to every reachable user
    // maxDepth limits how far to walk; -1 means no limit
    unordered_map<int, int> BFS(int start, int maxDepth) const;

    int userCount() const;
};

#endif // GRAPH_H
