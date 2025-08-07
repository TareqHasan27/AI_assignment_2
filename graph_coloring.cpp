#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <map>

using namespace std;

class GraphColoring {
private:
    unordered_map<string, vector<string>> graph;
    vector<string> colors;
    unordered_map<string, string> assigned;

    bool canAssign(const string& node, const string& color) {
        for (const string& neighbor : graph[node]) {
            if (assigned[neighbor] == color) return false;
        }
        return true;
    }

    bool solve(const vector<string>& nodes, int index) {
        if (index == nodes.size()) return true;
        string current = nodes[index];

        for (const string& color : colors) {
            if (canAssign(current, color)) {
                assigned[current] = color;
                if (solve(nodes, index + 1)) return true;
                assigned[current] = "";
            }
        }
        return false;
    }

public:
    void addEdge(const string& u, const string& v) {
        graph[u].push_back(v);
    }

    void addColor(const string& color) {
        colors.push_back(color);
    }

    void runColoring(const vector<string>& nodes) {
        assigned.clear();
        for (const string& node : nodes) {
            assigned[node] = "";
        }

        if (solve(nodes, 0)) {
            for (const string& node : nodes) {
                cout << node << " " << assigned[node] << endl;
            }

            map<string, int> count;
            for (const string& node : nodes) {
                count[assigned[node]]++;
            }
            for (const auto& entry : count) {
                cout << entry.first << ": " << entry.second << endl;
            }
        } else {
            cout << "No" << endl;
        }
    }
};

int main() {
    cout << "Demo Graph Coloring:" << endl;

    GraphColoring demo;
    vector<string> demoNodes = {"A", "B", "C", "D"};

    demo.addEdge("A", "B");
    demo.addEdge("A", "C");
    demo.addEdge("B", "C");
    demo.addEdge("B", "D");
    demo.addEdge("C", "D");

    demo.addColor("Red");
    demo.addColor("Green");
    demo.addColor("Blue");

    demo.runColoring(demoNodes);

    cout << "\nCustom Graph Coloring:" << endl;

    int n;
    cout << "Enter number of nodes:" << endl;
    cin >> n;
    cin.ignore();

    vector<string> userNodes;
    cout << "Enter node names:" << endl;
    for (int i = 0; i < n; ++i) {
        string name;
        getline(cin, name);
        userNodes.push_back(name);
    }

    GraphColoring userGraph;
    cout << "Enter adjacency list for each node (end with -1):" << endl;
    for (int i = 0; i < n; ++i) {
        string u = userNodes[i];
        while (true) {
            string v;
            cin >> v;
            if (v == "-1") break;
            userGraph.addEdge(u, v);
        }
    }

    int c;
    cout << "Enter number of colors:" << endl;
    cin >> c;
    cin.ignore();
    cout << "Enter colors:" << endl;
    for (int i = 0; i < c; ++i) {
        string color;
        getline(cin, color);
        userGraph.addColor(color);
    }

    userGraph.runColoring(userNodes);

    return 0;
}
