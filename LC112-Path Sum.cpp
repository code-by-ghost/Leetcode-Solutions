/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    bool solve(TreeNode* root, int targetSum, int sum){
        if(!root) return false;
        if(!root->left && !root->right) return (sum+root->val) == targetSum;

        bool left = solve(root->left, targetSum, root->val+sum);
        if(left) return true;
        bool right = solve(root->right, targetSum, root->val+sum);
        if(right) return true;

        return false;
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        return solve(root, targetSum, 0);
    }
};
