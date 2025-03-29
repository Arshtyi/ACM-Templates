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
// 基本BFS
void bfs(int start)
{
    // 初始化
    std::memset(visited, false, sizeof(visited));
    std::memset(dist, 0x3f, sizeof(dist));

    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    dist[start] = 0;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        // 处理当前节点
        // ...

        // 遍历所有邻居
        for (int next : adj[curr])
        {
            if (!visited[next])
            {
                visited[next] = true;
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
    }
}