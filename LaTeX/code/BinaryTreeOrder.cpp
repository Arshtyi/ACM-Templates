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