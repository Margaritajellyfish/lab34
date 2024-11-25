#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

const int SIZE = 11;  // Total number of users (nodes)

// Maximum interaction strength to invert the weights
const int MAX_INTERACTION_STRENGTH = 21; // Adjusted based on the highest interaction strength in edges

struct Edge {
    int src, dest, weight;
};

struct User {
    int id;
    string name;
};

typedef pair<int, int> Pair;
class SocialNetwork {
public:
    vector<vector<Pair>> adjList;
    unordered_map<int, User> users;

    SocialNetwork(vector<Edge> const &edges, vector<User> const &userList) {
        adjList.resize(SIZE);

        // Initialize users
        for (const auto &user : userList) {
            users[user.id] = user;
        }

        // Build the adjacency list with inverted weights (friendship distances)
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;

            // Invert the weight to represent distance
            int distance = MAX_INTERACTION_STRENGTH - edge.weight + 1;

            adjList[src].push_back(make_pair(dest, distance));
            adjList[dest].push_back(make_pair(src, distance));
        }
    }

    void printNetwork() {
        cout << "Social Media Network Connections:\n";
        cout << "=================================\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << users[i].name << " connects with:\n";
            for (Pair v : adjList[i]) {
                cout << "  → " << users[v.first].name << " (Friendship Distance: " << v.second << ")\n";
            }
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;
        int current = start;

        cout << "Friendship Exploration (DFS) starting from " << users[start].name << ":\n";
        cout << "=========================================================\n";

        while (true) {
            if (!visited[current]) {
                visited[current] = true;
                cout << "Visiting " << users[current].name << "\n";
            }

            vector<int> unvisited_neighbors;
            for (auto &neighbor : adjList[current]) {
                int adjVertex = neighbor.first;
                if (!visited[adjVertex]) {
                    unvisited_neighbors.push_back(adjVertex);
                }
            }

            if (!unvisited_neighbors.empty()) {
                // Proceed to the last unvisited neighbor
                int next = unvisited_neighbors.back();

                // Push other unvisited neighbors onto the stack
                for (int i = 0; i < unvisited_neighbors.size() - 1; ++i) {
                    s.push(unvisited_neighbors[i]);
                }

                // Move to the next node
                current = next;
            } else if (!s.empty()) {
                // No unvisited neighbors, pop from stack
                current = s.top();
                s.pop();
            } else {
                // Stack is empty, traversal is complete
                break;
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Layer-by-Layer Connection Inspection (BFS) from " << users[start].name << ":\n";
        cout << "============================================================\n";

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            cout << "Checking connections of " << users[vertex].name << "\n";

            for (auto &neighbor : adjList[vertex]) {
                int adjVertex = neighbor.first;
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    q.push(adjVertex);
                }
            }
        }
        cout << endl;
    }

    void shortestPath(int start) {
        // Dijkstra's algorithm
        vector<int> dist(SIZE, INT_MAX);
        dist[start] = 0;

        // Min-heap to store (distance, vertex)
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        // Output the shortest paths
        cout << "Shortest friendship distances from " << users[start].name << ":\n";
        for (int i = 0; i < SIZE; i++) {
            cout << users[start].name << " -> " << users[i].name << " : ";
            if (dist[i] == INT_MAX) {
                cout << "No connection\n";
            } else {
                cout << dist[i] << endl;
            }
        }
    }
};

int main() {
    vector<Edge> edges = {
        // Friendships between users with interaction strengths
        {0, 1, 8}, {0, 2, 21},
        {1, 2, 6}, {1, 3, 5}, {1, 4, 4},
        {2, 3, 7}, {2, 4, 12},
        {2, 5, 11}, {2, 6, 8},
        {3, 7, 9}, {4, 8, 10},
        {5, 6, 5}, {5, 7, 4}, {6, 8, 6},
        {7, 8, 3}, {5, 9, 15}, {6, 10, 7},
        {9, 10, 9}
    };

    // User information
    vector<User> userList = {
        {0, "Alice"}, {1, "Bob"}, {2, "Charlie"}, {3, "Diana"}, {4, "Eve"},
        {5, "Frank"}, {6, "Grace"}, {7, "Hannah"}, {8, "Ivan"}, {9, "Judy"}, {10, "Kevin"}
    };

    SocialNetwork network(edges, userList);
    network.printNetwork();
    network.DFS(0);
    network.BFS(0);
    network.shortestPath(0); // Compute shortest paths from Alice

    return 0;
}
