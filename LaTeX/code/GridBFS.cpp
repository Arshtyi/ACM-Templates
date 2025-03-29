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