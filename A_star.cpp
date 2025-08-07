#include <bits/stdc++.h>
using namespace std;

const int mx = 1e5 + 10;
vector<pair<int, int>> g[mx]; 
int H[mx]; 
int n, m;  

vector<int> a_star(int start, int end) {
    vector<long long> G(n + 1, LLONG_MAX); 
    G[start] = 0;
    priority_queue<pair<long long, int>> Q; 
    vector<bool> mark(n + 1, false);
    vector<int> previous(n + 1, -1);

    Q.push({-(G[start] + H[start]), start});

    while (!Q.empty()) {
        auto [_cost, u] = Q.top(); Q.pop();
        if (u == end) break;
        if (mark[u]) continue;
        mark[u] = true;

        for (auto [v, w] : g[u]) {
            if (!mark[v] && G[v] > G[u] + w) {
                G[v] = G[u] + w;
                previous[v] = u;
                Q.push({-(G[v] + H[v]), v});
            }
        }
    }

    if (G[end] == LLONG_MAX) return {}; 

    vector<int> path;
    for (int cur = end; cur != -1; cur = previous[cur])
        path.push_back(cur);

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    cout << "Enter number of nodes and edges:\n";
    cin >> n >> m;

    cout << "Enter " << m << " edges (format: u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w}); 
    }

    cout << "Enter heuristic values for each node (from 1 to " << n << "):\n";
    for (int i = 1; i <= n; i++) {
        cin >> H[i];
    }

    int start, end;
    cout << "Enter start and end node:\n";
    cin >> start >> end;

    vector<int> path = a_star(start, end);

    if (path.empty()) {
        cout << "No path found from " << start << " to " << end << endl;
    } else {
        cout << "Path found:\n";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
