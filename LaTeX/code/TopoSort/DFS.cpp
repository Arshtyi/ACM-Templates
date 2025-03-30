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
            if (!visited[v])
            {
                if (!dfs(v))
                    return false;
            }
            else if (inStack[v])
                return false; // 检测到环
        inStack[u] = false;   // 从递归栈中移除
        st.push(u);           // 添加到结果栈
        return true;
    };
    for (int i = 0; i < n; i++)
        if (!visited[i])
            if (!dfs(i))
                return {}; // 检测到环
    while (!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}