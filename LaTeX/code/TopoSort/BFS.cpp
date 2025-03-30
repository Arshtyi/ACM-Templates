vector<int> topoSortBFS(vector<vector<int>> &adj, int n)
{
    vector<int> result;
    vector<int> inDegree(n, 0);
    for (int u = 0; u < n; u++)
    {
        for (int v : adj[u])
        {
            inDegree[v]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }
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
    if (result.size() != n)
    {
        return {}; // 返回空向量表示存在环
    }
    return result;
}