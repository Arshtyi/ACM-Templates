// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;
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
        if (i < nums.size() && nums[i] != -1)
        {
            curr->left = new TreeNode(nums[i]);
            q.push(curr->left);
        }
        i++;
        if (i < nums.size() && nums[i] != -1)
        {
            curr->right = new TreeNode(nums[i]);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}