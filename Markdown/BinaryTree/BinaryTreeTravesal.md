# 二叉树建立

```c++
// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;
// 二叉树节点定义
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
}; // 使用数组构建二叉树（层次遍历顺序，-1表示空节点）
TreeNode *buildTree(vector<int> &nums)
{
    if (nums.empty() || nums[0] == -1)
        return nullptr;

    TreeNode *root = new TreeNode(nums[0]);
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < nums.size())
    {
        TreeNode *curr = q.front();
        q.pop();

        // 左子节点
        if (i < nums.size() && nums[i] != -1)
        {
            curr->left = new TreeNode(nums[i]);
            q.push(curr->left);
        }
        i++;

        // 右子节点
        if (i < nums.size() && nums[i] != -1)
        {
            curr->right = new TreeNode(nums[i]);
            q.push(curr->right);
        }
        i++;
    }

    return root;
}
```

# BFS层次遍历

```c++
// 层次遍历（BFS）
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    if (!root)
        return result;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        vector<int> currentLevel;

        for (int i = 0; i < size; i++)
        {
            TreeNode *node = q.front();
            q.pop();

            currentLevel.push_back(node->val);

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }

        result.push_back(currentLevel);
    }

    return result;
}
```

# 递归（前中后）序遍历

```c++
// 前序遍历 (根->左->右)
void preOrder(TreeNode *root)
{
    if (!root)
        return;

    cout << root->val << " "; // 处理当前节点
    preOrder(root->left);     // 递归遍历左子树
    preOrder(root->right);    // 递归遍历右子树
}

// 中序遍历 (左->根->右)
void inOrder(TreeNode *root)
{
    if (!root)
        return;

    inOrder(root->left);      // 递归遍历左子树
    cout << root->val << " "; // 处理当前节点
    inOrder(root->right);     // 递归遍历右子树
}

// 后序遍历 (左->右->根)
void postOrder(TreeNode *root)
{
    if (!root)
        return;

    postOrder(root->left);    // 递归遍历左子树
    postOrder(root->right);   // 递归遍历右子树
    cout << root->val << " "; // 处理当前节点
}
```

