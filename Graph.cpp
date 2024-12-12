#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

class Graph {
private:
    unordered_map<char, vector<pair<char, int>>> adjList;

public:
    void addEdge(char from, char to, int weight) {
        adjList[from].push_back({to, weight});
    }

    void DFS(char start) {
        unordered_map<char, bool> visited;
        stack<pair<char, int>> s;
        s.push({start, 0});
        int totalCost = 0;

        cout << "DFS Traversal:\n";
        while (!s.empty()) {
            auto [node, cost] = s.top();
            s.pop();

            if (!visited[node]) {
                visited[node] = true;
                totalCost += cost;
                cout << node << " (Cost: " << totalCost << ")\n";

                for (auto it = adjList[node].rbegin(); it != adjList[node].rend(); ++it) {
                    if (!visited[it->first]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << "Total Cost: " << totalCost << "\n\n";
    }

    void BFS(char start) {
        unordered_map<char, bool> visited;
        queue<pair<char, int>> q;
        q.push({start, 0});
        int totalCost = 0;

        cout << "BFS Traversal:\n";
        while (!q.empty()) {
            auto [node, cost] = q.front();
            q.pop();

            if (!visited[node]) {
                visited[node] = true;
                totalCost += cost;
                cout << node << " (Cost: " << totalCost << ")\n";

                for (const auto& neighbor : adjList[node]) {
                    if (!visited[neighbor.first]) {
                        q.push(neighbor);
                    }
                }
            }
        }
        cout << "Total Cost: " << totalCost << "\n\n";
    }

    void findPath(char source, char destination) {
        unordered_map<char, bool> visited;
        unordered_map<char, char> parent;
        queue<pair<char, int>> q;
        q.push({source, 0});
        visited[source] = true;

        bool pathExists = false;
        int pathLength = 0;

        while (!q.empty()) {
            auto [node, cost] = q.front();
            q.pop();

            if (node == destination) {
                pathExists = true;
                pathLength = cost;
                break;
            }

            for (const auto& neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    parent[neighbor.first] = node;
                    q.push({neighbor.first, cost + neighbor.second});
                }
            }
        }

        if (pathExists) {
            vector<char> path;
            for (char at = destination; at != source; at = parent[at]) {
                path.push_back(at);
            }
            path.push_back(source);
            reverse(path.begin(), path.end());

            cout << "Path from " << source << " to " << destination << ": ";
            for (char node : path) {
                cout << node << " ";
            }
            cout << "\nLength of path: " << pathLength << "\n\n";
        } else {
            cout << "No path exists from " << source << " to " << destination << "\n\n";
        }
    }
};

int main() {
    Graph graph;

    graph.addEdge('A', 'B', 1);
    graph.addEdge('A', 'C', 4);
    graph.addEdge('B', 'D', 2);
    graph.addEdge('B', 'E', 3);
    graph.addEdge('C', 'F', 5);
    graph.addEdge('E', 'F', 2);
    graph.addEdge('F', 'G', 1);

    char startNode = 'E';

    graph.DFS(startNode);
    graph.BFS(startNode);

    graph.findPath('E', 'G');
    graph.findPath('A', 'G');
    graph.findPath('A', 'Z');

    return 0;
}
