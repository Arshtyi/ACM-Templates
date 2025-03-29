// 线性查找 - O(n)
int linearSearch(vector<int> &arr, int target)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1; // 未找到
}
// 二分查找（要求数组有序）- O(log n)
int binarySearch(vector<int> &arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // 未找到
}
// 二分查找左边界 - O(log n)
int lowerBound(vector<int> &arr, int target)
{
    int left = 0, right = arr.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

// 二分查找右边界 - O(log n)
int upperBound(vector<int> &arr, int target)
{
    int left = 0, right = arr.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
// 广度优先搜索（BFS）- 图的遍历
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
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
} // 深度优先搜索（DFS）- 递归实现
void DFS(vector<vector<int>> &graph, vector<bool> &visited, int node)
{
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        {
            DFS(graph, visited, neighbor);
        }
    }
}

// DFS入口函数
void DFSTraversal(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    DFS(graph, visited, start);
}

// 迭代实现的DFS
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

            // 注意：为了与递归DFS相同的遍历顺序，这里反向压入邻居
            for (int i = graph[node].size() - 1; i >= 0; i--)
            {
                int neighbor = graph[node][i];
                if (!visited[neighbor])
                {
                    s.push(neighbor);
                }
            }
        }
    }
}