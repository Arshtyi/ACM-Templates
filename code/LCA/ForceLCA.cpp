// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstring>
// #include <functional>
// #include <unordered_map>
// using namespace std;
const int MAXN = 1e5 + 5;
const int LOGN = 20; // 2^20 > 10^6
class NaiveLCA
{
private:
    vector<vector<int>> graph;
    vector<int> depth;
    vector<int> parent;
    void dfs(int u, int p, int d)
    {
        parent[u] = p;
        depth[u] = d;
        for (int v : graph[u])
            if (v != p)
                dfs(v, u, d + 1);
    }

public:
    NaiveLCA(int n) : graph(n + 1), depth(n + 1), parent(n + 1) {}
    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    void preprocess(int root = 1)
    {
        dfs(root, -1, 0);
    }
    int lca(int u, int v)
    {
        // Equalize depths
        while (depth[u] > depth[v])
            u = parent[u];
        while (depth[v] > depth[u])
            v = parent[v];
        while (u != v)
        {
            u = parent[u];
            v = parent[v];
        }
        return u;
    }
};