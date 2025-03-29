# Kahn算法(基于BFS)

```c++
vector<int> topoSortBFS(vector<vector<int>> &adj, int n)
{
    vector<int> result;
    vector<int> inDegree(n, 0);

    // 计算每个顶点的入度
    for (int u = 0; u < n; u++)
    {
        for (int v : adj[u])
        {
            inDegree[v]++;
        }
    }

    // 将所有入度为0的顶点加入队列
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    // 处理队列中的顶点
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : adj[u])
        {
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    // 如果结果大小不等于节点数，说明存在环
    if (result.size() != n)
    {
        return {}; // 返回空向量表示存在环
    }

    return result;
}
```

# DFS方法

```c++
vector<int> topoSortDFS(vector<vector<int>> &adj, int n)
{
    vector<int> result;
    vector<bool> visited(n, false);
    vector<bool> inStack(n, false); // 用于检测环
    stack<int> st;

    function<bool(int)> dfs = [&](int u) -> bool
    {
        visited[u] = true;
        inStack[u] = true;

        for (int v : adj[u])
        {
            if (!visited[v])
            {
                if (!dfs(v))
                    return false;
            }
            else if (inStack[v])
            {
                return false; // 检测到环
            }
        }

        inStack[u] = false; // 从递归栈中移除
        st.push(u);         // 添加到结果栈
        return true;
    };

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (!dfs(i))
            {
                return {}; // 检测到环
            }
        }
    }

    // 从栈中弹出顶点获得拓扑排序
    while (!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}
```

