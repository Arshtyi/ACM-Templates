// #include <iostream>
// #include <vector>
// #include <stack>
// using namespace std;
const int MAXN = 1e5 + 5; // 最大节点数
// 邻接表表示图
vector<int> adj[MAXN];
bool visited[MAXN];
// 迭代实现DFS
void dfs_iterative(int start)
{
    stack<int> s;

    // 初始化所有节点为未访问
    fill(visited, visited + MAXN, false);

    // 将起始节点压入栈中
    s.push(start);

    while (!s.empty())
    {
        int u = s.top();
        s.pop();

        // 如果节点未被访问
        if (!visited[u])
        {
            // 标记为已访问并处理
            visited[u] = true;
            cout << u << " ";

            // 将所有未访问的邻接节点压入栈中（注意：倒序压入以保持与递归DFS相同的访问顺序）
            for (int i = adj[u].size() - 1; i >= 0; --i)
            {
                int v = adj[u][i];
                if (!visited[v])
                {
                    s.push(v);
                }
            }
        }
    }
}