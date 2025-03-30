// #include <iostream>
// #include <vector>
// #include <stack>
// using namespace std;
const int MAXN = 1e5 + 5; // 最大节点数
vector<int> adj[MAXN];
bool visited[MAXN];
void dfs_iterative(int start)
{
    stack<int> s;
    fill(visited, visited + MAXN, false);
    s.push(start);
    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        if (!visited[u])
        {
            visited[u] = true;
            cout << u << " ";
            for (int i = adj[u].size() - 1; i >= 0; --i)
            {
                int v = adj[u][i];
                if (!visited[v])
                    s.push(v);
            }
        }
    }
}