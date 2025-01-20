/*
2099. Find Subsequence of Length K With the Largest Sum

You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.



Example 1:

Input: nums = [2,1,3,3], k = 2
Output: [3,3]
Explanation:
The subsequence has the largest sum of 3 + 3 = 6.

Example 2:

Input: nums = [-1,-2,3,4], k = 3
Output: [-1,3,4]
Explanation:
The subsequence has the largest sum of -1 + 3 + 4 = 6.

*/
// TC = O(nlogn*k)   SC = O(n)

class Solution
{
public:
    vector<int> maxSubsequence(vector<int> &nums, int k)
    {
        vector<int> res;
        vector<int> temp = nums;
        sort(temp.begin(), temp.end(), greater<int>());
        unordered_map<int, int> mpp;
        for (int i = 0; i < k; i++)
        {
            mpp[temp[i]]++;
        }
        for (auto it : nums)
        {
            if (mpp[it]-- > 0)
                res.push_back(it);
        }
        return res;
    }
};