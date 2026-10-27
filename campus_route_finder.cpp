
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

class CampusGraph {
private:
    vector<string> locations;
    vector<vector<int>> adj;

    int findLocation(string name) {
        for (int i = 0; i < locations.size(); i++) {
            if (locations[i] == name)
                return i;
        }
        return -1;
    }

public:
    CampusGraph() {
        locations = {
            "Main Gate", "Library", "Block 1", "Block 2",
            "Cafeteria", "Auditorium", "Parking", "Lab"
        };

        adj.resize(locations.size());

        addEdge("Main Gate", "Library");
        addEdge("Main Gate", "Parking");
        addEdge("Library", "Block 1");
        addEdge("Library", "Cafeteria");
        addEdge("Block 1", "Block 2");
        addEdge("Block 1", "Lab");
        addEdge("Block 2", "Auditorium");
        addEdge("Cafeteria", "Auditorium");
        addEdge("Parking", "Cafeteria");
    }

    void addEdge(string a, string b) {
        int u = findLocation(a);
        int v = findLocation(b);

        if (u != -1 && v != -1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void displayLocations() {
        cout << "\nCampus Locations:\n";
        for (int i = 0; i < locations.size(); i++)
            cout << i + 1 << ". " << locations[i] << '\n';
    }

    void displayGraph() {
        cout << "\nAdjacency List:\n";

        for (int i = 0; i < locations.size(); i++) {
            cout << locations[i] << ": ";

            for (int j = 0; j < adj[i].size(); j++) {
                cout << locations[adj[i][j]];
                if (j + 1 < adj[i].size())
                    cout << ", ";
            }
            cout << '\n';
        }
    }

    void BFS(string sourceName, string destinationName) {
        int source = findLocation(sourceName);
        int destination = findLocation(destinationName);

        if (source == -1 || destination == -1) {
            cout << "Invalid location name!\n";
            return;
        }

        vector<bool> visited(locations.size(), false);
        vector<int> parent(locations.size(), -1);
        queue<int> q;

        visited[source] = true;
        q.push(source);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == destination)
                break;

            for (int next : adj[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    parent[next] = current;
                    q.push(next);
                }
            }
        }

        if (!visited[destination]) {
            cout << "No route exists!\n";
            return;
        }

        vector<int> path;

        for (int current = destination;
             current != -1;
             current = parent[current]) {
            path.push_back(current);
        }

        reverse(path.begin(), path.end());

        cout << "\nShortest route using BFS:\n";

        for (int i = 0; i < path.size(); i++) {
            cout << locations[path[i]];

            if (i + 1 < path.size())
                cout << " -> ";
        }

        cout << "\nNumber of edges: "
             << path.size() - 1 << '\n';
    }

    void DFS(string sourceName) {
        int source = findLocation(sourceName);

        if (source == -1) {
            cout << "Invalid location name!\n";
            return;
        }

        vector<bool> visited(locations.size(), false);
        stack<int> st;

        st.push(source);

        cout << "\nDFS Traversal:\n";

        while (!st.empty()) {
            int current = st.top();
            st.pop();

            if (visited[current])
                continue;

            visited[current] = true;
            cout << locations[current] << '\n';

            for (auto it = adj[current].rbegin();
                 it != adj[current].rend(); ++it) {
                if (!visited[*it])
                    st.push(*it);
            }
        }
    }

    void showReachability(string sourceName) {
        int source = findLocation(sourceName);

        if (source == -1) {
            cout << "Invalid location name!\n";
            return;
        }

        vector<bool> visited(locations.size(), false);
        queue<int> q;

        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int next : adj[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        cout << "\nReachable Locations:\n";
        for (int i = 0; i < locations.size(); i++) {
            if (visited[i])
                cout << locations[i] << '\n';
        }

        cout << "\nDisconnected Locations:\n";
        bool found = false;

        for (int i = 0; i < locations.size(); i++) {
            if (!visited[i]) {
                cout << locations[i] << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "None. All locations are connected.\n";
    }
};

int main() {
    CampusGraph campus;
    int choice;

    do {
        cout << "\n===== CAMPUS ROUTE FINDER =====\n";
        cout << "1. Display Locations\n";
        cout << "2. Display Adjacency List\n";
        cout << "3. Find Shortest Route (BFS)\n";
        cout << "4. DFS Traversal\n";
        cout << "5. Reachability Check\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            return 0;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string source, destination;

        switch (choice) {
            case 1:
                campus.displayLocations();
                break;

            case 2:
                campus.displayGraph();
                break;

            case 3:
                cout << "Enter source: ";
                getline(cin, source);
                cout << "Enter destination: ";
                getline(cin, destination);
                campus.BFS(source, destination);
                break;

            case 4:
                cout << "Enter starting location: ";
                getline(cin, source);
                campus.DFS(source);
                break;

            case 5:
                cout << "Enter starting location: ";
                getline(cin, source);
                campus.showReachability(source);
                break;

            case 0:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
