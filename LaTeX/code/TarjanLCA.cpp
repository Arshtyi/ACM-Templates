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