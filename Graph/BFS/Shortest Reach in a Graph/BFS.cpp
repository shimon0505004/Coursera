//https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <fstream>

using namespace std;

class Graph {
public:
    Graph(int n) {
        mAdjacencyList.clear();
        for (int nodeID = 0; nodeID<n; nodeID++)
        {
            std::unordered_set<int> adjacentNodes;
            adjacentNodes.clear();
            mAdjacencyList.emplace(nodeID, adjacentNodes);
            mPrevNode.emplace(nodeID, -1);
            mShortestDistance.emplace(nodeID, 0);
        }
    }

    void add_edge(int u, int v) {
        if (mAdjacencyList.count(u))
            mAdjacencyList.at(u).insert(v);
        else
        {
            std::unordered_set<int> adjacentNodes;
            adjacentNodes.insert(v);
            mAdjacencyList.emplace(u, adjacentNodes);
        }
        if (mAdjacencyList.count(v))
            mAdjacencyList.at(v).insert(u);
        else
        {
            std::unordered_set<int> adjacentNodes;
            adjacentNodes.insert(u);
            mAdjacencyList.emplace(v, adjacentNodes);
        }

    }

    vector<int> shortest_reach(int start) {
        std::queue<int> BFSQueue;
        BFSQueue.push(start);
        mShortestDistance.at(start) = 0;
        mPrevNode.at(start) = -1;
        while (!BFSQueue.empty())
        {
            int node = BFSQueue.front();
            BFSQueue.pop();
            for (const auto& adjNode : mAdjacencyList.at(node))
            {
                if (mPrevNode.at(adjNode) == -1)
                {
                    int newShortestDist = mShortestDistance.at(node) + weightOfEachNode;
                    mShortestDistance.at(adjNode) = newShortestDist;
                    mPrevNode.at(adjNode) = node;
                    BFSQueue.push(adjNode);
                }
            }
        }

        vector<int> result;
        for (int nodeID = 0; nodeID<mShortestDistance.size(); nodeID++)
        {
            if (mShortestDistance.at(nodeID))
                result.push_back(mShortestDistance.at(nodeID));
            else
                result.push_back(-1);
        }
        return result;
    }
private:
    std::unordered_map<int, std::unordered_set<int>> mAdjacencyList;
    std::unordered_map<int, int> mShortestDistance;
    std::unordered_map<int, int> mPrevNode;
    int weightOfEachNode = 6;
};

int main() {
    int queries;
    cin >> queries;

    for (int t = 0; t < queries; t++) {

        int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
        int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
