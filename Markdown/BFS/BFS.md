# 基本BFS

```c++
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
```

# 路径重建

```c++
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
```

# 网格BFS

```c++
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
// 网格BFS
// 四个方向：上、右、下、左
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
void gridBfs(int startX, int startY, int rows, int cols, std::vector<std::vector<char>> &grid)
{
    bool vis[rows][cols];
    memset(vis, false, sizeof(vis));

    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    vis[startX][startY] = true;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        // 处理当前格子
        // ...

        // 遍历四个方向
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 检查边界和访问状态
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                !vis[nx][ny] && grid[nx][ny] != '#')
            { // '#'表示障碍
                vis[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}
```

