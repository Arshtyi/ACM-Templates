// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <queue>
// using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 5;
// Prim's Algorithm for MST
ll prim(vector<vector<pair<int, ll>>> &adj, int n)
{
    vector<bool> visited(n + 1, false);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    ll mstWeight = 0;
    int edgesAdded = 0;

    // Start from vertex 1
    pq.push({0, 1});

    while (!pq.empty() && edgesAdded < n)
    {
        ll w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        mstWeight += w;
        edgesAdded++;

        for (auto &[v, weight] : adj[u])
        {
            if (!visited[v])
            {
                pq.push({weight, v});
            }
        }
    }

    return (edgesAdded == n) ? mstWeight : -1; // Return -1 if MST doesn't exist
}

// Alternative implementation of Prim's algorithm using arrays (faster for dense graphs)
ll primDense(vector<vector<ll>> &graph, int n)
{
    vector<bool> visited(n + 1, false);
    vector<ll> key(n + 1, LLONG_MAX);

    key[1] = 0; // Start from vertex 1
    ll mstWeight = 0;

    for (int i = 0; i < n; i++)
    {
        int u = -1;

        // Find the vertex with minimum key value
        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && (u == -1 || key[v] < key[u]))
            {
                u = v;
            }
        }

        if (u == -1 || key[u] == LLONG_MAX)
            return -1; // MST doesn't exist

        visited[u] = true;
        mstWeight += key[u];

        // Update key values of adjacent vertices
        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
            }
        }
    }

    return mstWeight;
}