void DFS(vector<vector<int>> &graph, vector<bool> &visited, int node)
{
    visited[node] = true;
    cout << node << " ";
    for (int neighbor : graph[node])
        if (!visited[neighbor])
            DFS(graph, visited, neighbor);
}
void DFSTraversal(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    DFS(graph, visited, start);
}
void DFSIterative(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start);
    while (!s.empty())
    {
        int node = s.top();
        s.pop();
        if (!visited[node])
        {
            visited[node] = true;
            cout << node << " ";
            for (int i = graph[node].size() - 1; i >= 0; i--)
            {
                int neighbor = graph[node][i];
                if (!visited[neighbor])
                    s.push(neighbor);
            }
        }
    }
}