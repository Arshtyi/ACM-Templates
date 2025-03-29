// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <queue>
// using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 5;
// Edge structure
struct Edge
{
    int u, v;
    ll w;
    Edge(int _u = 0, int _v = 0, ll _w = 0) : u(_u), v(_v), w(_w) {}
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

// Disjoint Set Union (DSU) for Kruskal's algorithm
class DSU
{
private:
    vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
            return false;

        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else
        {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY])
            {
                rank[rootX]++;
            }
        }
        return true;
    }
};

// Kruskal's Algorithm for MST
ll kruskal(vector<Edge> &edges, int n)
{
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll mstWeight = 0;
    int edgesAdded = 0;

    for (Edge &e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            mstWeight += e.w;
            edgesAdded++;
            if (edgesAdded == n - 1)
                break;
        }
    }

    return (edgesAdded == n - 1) ? mstWeight : -1; // Return -1 if MST doesn't exist
}