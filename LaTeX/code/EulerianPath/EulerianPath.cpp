// #include <iostream>
// #include <vector>
// #include <stack>
// #include <algorithm>
// using namespace std;
class EulerPath
{
private:
    int n;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list
public:
    EulerPath(int n) : n(n)
    {
        adj.resize(n);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool hasEdges(int v, vector<vector<bool>> &visited)
    {
        for (int u : adj[v])
        {
            if (!visited[v][u])
                return true;
        }
        return false;
    }
    bool hasEulerPath()
    {
        int oddDegreeCount = 0;
        for (int i = 0; i < n; i++)
            if (adj[i].size() % 2)
                oddDegreeCount++;
        return oddDegreeCount == 0 || oddDegreeCount == 2;
    }
    bool hasEulerCircuit()
    {
        for (int i = 0; i < n; i++)
            if (adj[i].size() % 2)
                return false;
        return true;
    }
    vector<int> findEulerPath()
    {
        if (!hasEulerPath())
            return {}; // No Euler path exists
        int start = 0;
        for (int i = 0; i < n; i++)
            if (adj[i].size() % 2)
            {
                start = i;
                break;
            }
        vector<int> path;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        stack<int> st;
        st.push(start);
        while (!st.empty())
        {
            int v = st.top();
            if (hasEdges(v, visited))
                for (int u : adj[v])
                    if (!visited[v][u])
                    {
                        visited[v][u] = visited[u][v] = true;
                        st.push(u);
                        break;
                    }
                    else
                    {
                        path.push_back(v);
                        st.pop();
                    }
        }
        reverse(path.begin(), path.end());
        return path;
    }
};