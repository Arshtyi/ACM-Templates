# 暴力求解

```c++
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstring>
// #include <functional>
// #include <unordered_map>
// using namespace std;
const int MAXN = 1e5 + 5;
const int LOGN = 20; // 2^20 > 10^6
/* ---------- 1. Naive/Brute Force LCA ---------- */
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
        {
            if (v != p)
            {
                dfs(v, u, d + 1);
            }
        }
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

        // Move up until finding LCA
        while (u != v)
        {
            u = parent[u];
            v = parent[v];
        }
        return u;
    }
};
```

# 倍增LCA

```c++
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstring>
// #include <functional>
// #include <unordered_map>
// using namespace std;
const int MAXN = 1e5 + 5;
const int LOGN = 20; // 2^20 > 10^6
/* ---------- 2. Binary Lifting LCA ---------- */
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
        {
            if (up[u][j - 1] != -1)
                up[u][j] = up[up[u][j - 1]][j - 1];
            else
                up[u][j] = -1;
        }

        for (int v : graph[u])
        {
            if (v != p)
            {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
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

        // Equalize depths
        int diff = depth[u] - depth[v];
        for (int j = log_n; j >= 0; j--)
        {
            if (diff & (1 << j))
                u = up[u][j];
        }

        if (u == v)
            return u;

        // Binary lift to find LCA
        for (int j = log_n; j >= 0; j--)
        {
            if (up[u][j] != up[v][j])
            {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }
};
```

# ST+RMQ

```c++
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstring>
// #include <functional>
// #include <unordered_map>
// using namespace std;
const int MAXN = 1e5 + 5;
const int LOGN = 20; // 2^20 > 10^6
/* ---------- 3. ST + RMQ LCA ---------- */
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
        {
            if (v != p)
            {
                dfs(v, u, h + 1);
                euler.push_back(u);
            }
        }
    }

    void buildSparseTable()
    {
        int m = euler.size();
        int k = 0;
        while ((1 << k) <= m)
            k++;
        st.resize(m, vector<int>(k, 0));

        // Initialize with individual elements
        for (int i = 0; i < m; i++)
            st[i][0] = i;

        // Build sparse table
        for (int j = 1; j < k; j++)
        {
            for (int i = 0; i + (1 << j) <= m; i++)
            {
                int left = st[i][j - 1];
                int right = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = (height[euler[left]] < height[euler[right]]) ? left : right;
            }
        }
    }

    int rmq(int l, int r)
    {
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len); // log₂(len)
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
```

# Tarjan

```c++
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cstring>
// #include <functional>
// #include <unordered_map>
// using namespace std;
const int MAXN = 1e5 + 5;
const int LOGN = 20; // 2^20 > 10^6
/* ---------- 4. Tarjan's Offline LCA ---------- */
class TarjanLCA
{
private:
    vector<vector<int>> graph;
    vector<vector<pair<int, int>>> queries;
    vector<int> parent, rank;
    vector<bool> visited;
    vector<int> answer;

    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
            return;
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else
        {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY])
                rank[rootX]++;
        }
    }

    void tarjan(int u)
    {
        parent[u] = u;
        visited[u] = true;

        for (int v : graph[u])
        {
            if (!visited[v])
            {
                tarjan(v);
                unite(u, v);
                parent[find(v)] = u;
            }
        }

        for (auto q : queries[u])
        {
            int v = q.first;
            int idx = q.second;
            if (visited[v])
            {
                answer[idx] = find(v);
            }
        }
    }

public:
    TarjanLCA(int n, int q)
    {
        graph.resize(n + 1);
        queries.resize(n + 1);
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        visited.resize(n + 1, false);
        answer.resize(q, -1);
    }

    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void addQuery(int u, int v, int idx)
    {
        queries[u].push_back({v, idx});
        queries[v].push_back({u, idx});
    }

    vector<int> solve(int root = 1)
    {
        tarjan(root);
        return answer;
    }
};
```

