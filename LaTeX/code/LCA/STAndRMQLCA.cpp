// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstring>
// #include <functional>
// #include <unordered_map>
// using namespace std;
const int MAXN = 1e5 + 5;
const int LOGN = 20; // 2^20 > 10^6
class RMQLCA
{
private:
    vector<vector<int>> graph;
    vector<int> euler, first, height;
    vector<vector<int>> st; // Sparse Table
    int n, e_idx;
    void dfs(int u, int p, int h)
    {
        first[u] = euler.size();
        euler.push_back(u);
        height[u] = h;
        for (int v : graph[u])
            if (v != p)
            {
                dfs(v, u, h + 1);
                euler.push_back(u);
            }
    }
    void buildSparseTable()
    {
        int m = euler.size();
        int k = 0;
        while ((1 << k) <= m)
            k++;
        st.resize(m, vector<int>(k, 0));
        for (int i = 0; i < m; i++)
            st[i][0] = i;
        for (int j = 1; j < k; j++)
            for (int i = 0; i + (1 << j) <= m; i++)
            {
                int left = st[i][j - 1];
                int right = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = (height[euler[left]] < height[euler[right]]) ? left : right;
            }
    }
    int rmq(int l, int r)
    {
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len); // log(len)
        int a = st[l][k];
        int b = st[r - (1 << k) + 1][k];
        return (height[euler[a]] <= height[euler[b]]) ? a : b;
    }

public:
    RMQLCA(int size) : n(size)
    {
        graph.resize(n + 1);
        first.resize(n + 1, -1);
        height.resize(n + 1, 0);
        e_idx = 0;
    }
    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    void preprocess(int root = 1)
    {
        euler.clear();
        dfs(root, -1, 0);
        buildSparseTable();
    }
    int lca(int u, int v)
    {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return euler[rmq(left, right)];
    }
};