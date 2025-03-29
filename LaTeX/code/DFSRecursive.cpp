// #include <iostream>
// #include <vector>
// #include <stack>
// using namespace std;
const int MAXN = 1e5 + 5; // 最大节点数
// 邻接表表示图
vector<int> adj[MAXN];
bool visited[MAXN];
// 递归实现DFS
void dfs_recursive(int u)
{
    // 标记当前节点已访问
    visited[u] = true;

    // 处理当前节点
    cout << u << " ";

    // 遍历所有相邻节点
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs_recursive(v);
        }
    }
}