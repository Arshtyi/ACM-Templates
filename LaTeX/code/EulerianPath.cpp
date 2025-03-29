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

    // Check if a vertex has any unvisited edges
    bool hasEdges(int v, vector<vector<bool>> &visited)
    {
        for (int u : adj[v])
        {
            if (!visited[v][u])
                return true;
        }
        return false;
    }

    // Check if graph has Euler path
    bool hasEulerPath()
    {
        int oddDegreeCount = 0;
        for (int i = 0; i < n; i++)
        {
            if (adj[i].size() % 2 != 0)
                oddDegreeCount++;
        }
        return oddDegreeCount == 0 || oddDegreeCount == 2;
    }

    // Check if graph has Euler circuit
    bool hasEulerCircuit()
    {
        for (int i = 0; i < n; i++)
        {
            if (adj[i].size() % 2 != 0)
                return false;
        }
        return true;
    }

    // Hierholzer's algorithm to find Euler path/circuit
    vector<int> findEulerPath()
    {
        if (!hasEulerPath())
            return {}; // No Euler path exists

        // Find start vertex (first vertex with odd degree, or any if all even)
        int start = 0;
        for (int i = 0; i < n; i++)
        {
            if (adj[i].size() % 2 != 0)
            {
                start = i;
                break;
            }
        }

        vector<int> path;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        stack<int> st;
        st.push(start);

        while (!st.empty())
        {
            int v = st.top();

            if (hasEdges(v, visited))
            {
                for (int u : adj[v])
                {
                    if (!visited[v][u])
                    {
                        visited[v][u] = visited[u][v] = true;
                        st.push(u);
                        break;
                    }
                }
            }
            else
            {
                path.push_back(v);
                st.pop();
            }
        }

        // Path needs to be reversed to get the correct order
        reverse(path.begin(), path.end());
        return path;
    }
};