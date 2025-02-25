/*
1530. Number of Good Leaf Nodes Pairs

You are given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.

Return the number of good leaf node pairs in the tree.
*/

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
class Solution
{
public:
    int cnt = 0;
    vector<int> calcPairs(TreeNode *root, int dist)
    {
        if ((root->left == NULL) && (root->right == NULL))
        {
            vector<int> v1;
            return v1;
        }
        vector<int> left;
        vector<int> right;
        if (root->left)
        {
            left = calcPairs(root->left, dist);
            if (left.size() == 0)
                left.push_back(1);
        }
        if (root->right)
        {
            right = calcPairs(root->right, dist);
            if (right.size() == 0)
                right.push_back(1);
        }
        for (int i = 0; i < left.size(); i++)
        {
            for (int j = 0; j < right.size(); j++)
            {
                if (left[i] + right[j] <= dist)
                    cnt++;
            }
        }
        int i = 0;
        for (i = 0; i < left.size(); i++)
            ++left[i];
        while (i < right.size())
        {
            left.push_back(right[i] + 1);
            i++;
        }
        return left;
    }
    int countPairs(TreeNode *root, int distance)
    {
        vector<int> v = calcPairs(root, distance);
        return cnt;
    }
};