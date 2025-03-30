void BFS(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for (int neighbor : graph[node])
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
    }
}