// #include <iostream>
// #include <vector>
// #include <queue>
// #include <cstring>
// #include <algorithm>
// 常量定义
const int MAXN = 1e5 + 5;   // 最大节点数
const int INF = 0x3f3f3f3f; // 无穷大值
// 图的邻接表表示
std::vector<int> adj[MAXN];
bool visited[MAXN];
int dist[MAXN]; // 从源点到各点的距离
// 带路径重建的BFS
std::vector<int> bfsPath(int start, int end)
{
    std::memset(visited, false, sizeof(visited));
    int parent[MAXN];
    std::memset(parent, -1, sizeof(parent));

    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty() && !visited[end])
    {
        int curr = q.front();
        q.pop();

        for (int next : adj[curr])
        {
            if (!visited[next])
            {
                visited[next] = true;
                parent[next] = curr;
                q.push(next);
            }
        }
    }

    // 重建路径
    std::vector<int> path;
    if (visited[end])
    {
        for (int at = end; at != -1; at = parent[at])
        {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}