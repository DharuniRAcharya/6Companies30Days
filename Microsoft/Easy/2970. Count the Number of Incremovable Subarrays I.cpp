/*
2970. Count the Number of Incremovable Subarrays I

You are given a 0-indexed array of positive integers nums.

A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.

Return the total number of incremovable subarrays of nums.

Note that an empty array is considered strictly increasing.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [1,2,3,4]
Output: 10
Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing. Note that you cannot select an empty subarray.

Example 2:

Input: nums = [6,5,7,8]
Output: 7
Explanation: The 7 incremovable subarrays are: [5], [6], [5,7], [6,5], [5,7,8], [6,5,7] and [6,5,7,8].
It can be shown that there are only 7 incremovable subarrays in nums.

*/

// Approach - Constraints are small => Brute force solution
// TC = O(n^3)  SC = O(1)

class Solution
{
public:
    int incremovableSubarrayCount(vector<int> &nums)
    {
        int ans = 0;
        int n = nums.size();

        // Outer loop for the start index of the subarray
        for (int i = 0; i < n; i++)
        {
            // Inner loop for the end index of the subarray
            for (int j = i; j < n; j++)
            {
                bool check = true; // Flag to check if subarray is increasing
                int last_ele = -1; // Variable to keep track of the last element

                // Loop to check each element within or outside the subarray
                for (int k = 0; k < n; k++)
                {
                    if (k >= i && k <= j)
                    {
                        // Elements within the subarray are skipped
                    }
                    else
                    {
                        check &= (last_ele < nums[k]); // Check if the current element is greater than the last one
                        last_ele = nums[k];            // Update the last element
                    }
                }

                ans += check; // Increment count if the subarray is "incremovable"
            }
        }
        return ans; // Return the total count of "incremovable" subarrays
    }
};
