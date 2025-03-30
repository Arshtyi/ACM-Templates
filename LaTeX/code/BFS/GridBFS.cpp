// #include <iostream>
// #include <vector>
// #include <queue>
// #include <cstring>
// #include <algorithm>
// 常量定义
const int MAXN = 1e5 + 5;   // 最大节点数
const int INF = 0x3f3f3f3f; // 无穷大值
std::vector<int> adj[MAXN];
bool visited[MAXN];
int dist[MAXN]; // 从源点到各点的距离
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
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
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                !vis[nx][ny] && grid[nx][ny] != '#')
            { // '#'表示障碍
                vis[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}