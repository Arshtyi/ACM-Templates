// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstring>
// #include <functional>
// #include <unordered_map>
// using namespace std;
const int MAXN = 1e5 + 5;
const int LOGN = 20; // 2^20 > 10^6
class BinaryLiftingLCA
{
private:
    vector<vector<int>> graph;
    vector<vector<int>> up; // up[i][j] = 2^j-th ancestor of node i
    vector<int> depth;
    int n, log_n;
    void dfs(int u, int p)
    {
        up[u][0] = p;
        for (int j = 1; j <= log_n; j++)
            if (up[u][j - 1] != -1)
                up[u][j] = up[up[u][j - 1]][j - 1];
            else
                up[u][j] = -1;
        for (int v : graph[u])
            if (v != p)
            {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
    }

public:
    BinaryLiftingLCA(int size) : n(size)
    {
        log_n = 0;
        while ((1 << log_n) <= n)
            log_n++;
        graph.resize(n + 1);
        up.resize(n + 1, vector<int>(log_n + 1, -1));
        depth.resize(n + 1, 0);
    }
    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    void preprocess(int root = 1)
    {
        depth[root] = 0;
        dfs(root, -1);
    }
    int lca(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        int diff = depth[u] - depth[v];
        for (int j = log_n; j >= 0; j--)
            if (diff & (1 << j))
                u = up[u][j];
        if (u == v)
            return u;
        for (int j = log_n; j >= 0; j--)
            if (up[u][j] != up[v][j])
            {
                u = up[u][j];
                v = up[v][j];
            }
        return up[u][0];
    }
};