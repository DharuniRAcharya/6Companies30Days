/*
1385. Find the Distance Value Between Two Arrays

Given two integer arrays arr1 and arr2, and the integer d, return the distance value between the two arrays.

The distance value is defined as the number of elements arr1[i] such that there is not any element arr2[j] where |arr1[i]-arr2[j]| <= d.

Example 1:

Input: arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
Output: 2
Explanation:
For arr1[0]=4 we have:
|4-10|=6 > d=2
|4-9|=5 > d=2
|4-1|=3 > d=2
|4-8|=4 > d=2
For arr1[1]=5 we have:
|5-10|=5 > d=2
|5-9|=4 > d=2
|5-1|=4 > d=2
|5-8|=3 > d=2
For arr1[2]=8 we have:
|8-10|=2 <= d=2
|8-9|=1 <= d=2
|8-1|=7 > d=2
|8-8|=0 <= d=2

*/

// T(n**2) SC(1)
// Brute force solution

class Solution
{
public:
    int findTheDistanceValue(vector<int> &arr1, vector<int> &arr2, int d)
    {
        int res = 0;
        int n = arr1.size(), m = arr2.size();
        for (int i = 0; i < n; i++)
        {
            bool find = true;
            for (int j = 0; j < m; j++)
            {
                if (abs(arr1[i] - arr2[j]) <= d)
                {
                    find = false;
                    break;
                }
            }
            if (find)
                res++;
        }
        return res;
    }
};

// Binary Search solution

class Solution
{
public:
    bool isValid(vector<int> &arr, int target, int d)
    {

        int low = 0, high = arr.size() - 1;
        while (low <= high)
        {

            int mid = low + (high - low) / 2;
            if (abs(arr[mid] - target) <= d)
            {
                return false;
            }
            else if (arr[mid] < target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return true;
    }

    int findTheDistanceValue(vector<int> &arr1, vector<int> &arr2, int d)
    {

        sort(arr2.begin(), arr2.end());

        int cnt = 0;
        for (auto num : arr1)
        {
            if (isValid(arr2, num, d))
            {
                cnt++;
            }
        }

        return cnt;
    }
};