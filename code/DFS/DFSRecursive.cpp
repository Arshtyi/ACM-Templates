// #include <iostream>
// #include <vector>
// #include <stack>
// using namespace std;
const int MAXN = 1e5 + 5; // 最大节点数
vector<int> adj[MAXN];
bool visited[MAXN];
void dfs_recursive(int u)
{
    visited[u] = true;
    cout << u << " ";
    for (int v : adj[u])
        if (!visited[v])
            dfs_recursive(v);
}