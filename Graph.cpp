#include "Graph.h"
#include <queue>

using namespace std;

void Graph::addUser(int id)
{
    // only add if new
    if (adjacency.find(id) == adjacency.end())
    {
        adjacency[id] = unordered_set<int>();
    }
}

void Graph::addFriend(int a, int b)
{
    if (a == b)
    {
        return; // can't befriend yourself
    }
    addUser(a);
    addUser(b);

    // friendship goes both ways
    adjacency[a].insert(b);
    adjacency[b].insert(a);
}

bool Graph::hasUser(int id) const
{
    return adjacency.find(id) != adjacency.end();
}

unordered_set<int> Graph::getNeighbors(int id) const
{
    unordered_set<int> result;
    auto it = adjacency.find(id);
    if (it != adjacency.end())
    {
        result = it->second;
    }
    return result;
}

unordered_set<int> Graph::getMutualFriends(int a, int b) const
{
    unordered_set<int> mutual;
    unordered_set<int> friendsA = getNeighbors(a);
    unordered_set<int> friendsB = getNeighbors(b);

    // keep friends of a that are also friends of b
    for (int f : friendsA)
    {
        if (friendsB.find(f) != friendsB.end())
        {
            mutual.insert(f);
        }
    }
    return mutual;
}

unordered_map<int, int> Graph::BFS(int start, int maxDepth) const
{
    unordered_map<int, int> distance;

    if (!hasUser(start))
    {
        return distance;
    }

    queue<int> toVisit;
    distance[start] = 0;
    toVisit.push(start);

    while (!toVisit.empty())
    {
        int current = toVisit.front();
        toVisit.pop();

        int currentDepth = distance[current];

        // stop expanding once the depth limit is reached
        if (maxDepth >= 0 && currentDepth >= maxDepth)
        {
            continue;
        }

        unordered_set<int> neighbors = getNeighbors(current);
        for (int next : neighbors)
        {
            // first time we reach someone is the shortest distance
            if (distance.find(next) == distance.end())
            {
                distance[next] = currentDepth + 1;
                toVisit.push(next);
            }
        }
    }
    return distance;
}

int Graph::userCount() const
{
    return (int)adjacency.size();
}
