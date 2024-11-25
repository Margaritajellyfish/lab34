#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  
class Graph {
public:
    vector<vector<Pair> > adjList;

    Graph(vector<Edge> const &edges) {   
        adjList.resize(SIZE);

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void DFS(int start) {
    vector<bool> visited(SIZE, false);
    stack<int> s;
    int current = start;

    cout << "DFS traversal starting from vertex " << start << ": \n";

    while (true) {
        if (!visited[current]) {
            visited[current] = true;
            cout << current << " ";
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

        cout << "BFS traversal starting from vertex " << start << ": \n";

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();    
            cout << vertex << " ";

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
};

int main() {
    vector<Edge> edges = {
        {0, 1, 12}, {0, 2, 8}, {0, 3, 21},
        {2, 3, 6}, {2, 6, 2}, {5, 6, 6},
        {4, 5, 9}, {2, 4, 4}, {2, 5, 5}
    };

    Graph graph(edges);   
    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
