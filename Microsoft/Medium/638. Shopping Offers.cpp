/*
638. Shopping Offers
In LeetCode Store, there are n items to sell. Each item has a price. However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.

You are given an integer array price where price[i] is the price of the ith item, and an integer array needs where needs[i] is the number of pieces of the ith item you want to buy.

You are also given an array special where special[i] is of size n + 1 where special[i][j] is the number of pieces of the jth item in the ith offer and special[i][n] (i.e., the last integer in the array) is the price of the ith offer.

Return the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers. You are not allowed to buy more items than you want, even if that would lower the overall price. You could use any of the special offers as many times as you want.



Example 1:

Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
Output: 14
Explanation: There are two kinds of items, A and B. Their prices are $2 and $5 respectively.
In special offer 1, you can pay $5 for 3A and 0B
In special offer 2, you can pay $10 for 1A and 2B.
You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.

Example 2:

Input: price = [2,3,4], special = [[1,1,0,4],[2,2,1,9]], needs = [1,2,1]
Output: 11
Explanation: The price of A is $2, and $3 for B, $4 for C.
You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C.
You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C.
You cannot add more items, though only $9 for 2A ,2B and 1C.

*/

// Recursion approach => memory limit exceeded
class Solution
{
public:
    int solve(vector<int> &price, vector<vector<int>> &special, vector<int> needs, int index)
    {
        if (index == special.size())
        {
            int res = 0;
            for (int i = 0; i < needs.size(); i++)
            {
                res += needs[i] * price[i];
            }
            return res;
        }
        int reject = solve(price, special, needs, index + 1);
        bool cantake = true;
        for (int i = 0; i < needs.size(); i++)
        {
            needs[i] -= special[index][i];
            if (needs[i] < 0)
                cantake = false;
        }
        int accept = cantake ? special[index].back() + solve(price, special, needs, index) : reject;
        return min(reject, accept);
    }
    int shoppingOffers(vector<int> &price, vector<vector<int>> &special, vector<int> &needs)
    {
        return solve(price, special, needs, 0);
    }
};

// memo -> unordered_map<string, int> // needs array to string
// TC = O(2**N) SC = O(2**N)

class Solution
{
public:
    int shoppingOffers(vector<int> &price, vector<vector<int>> &special, vector<int> &needs)
    {
        // Use an unordered_map for memoization to avoid recomputing
        unordered_map<string, int> memo;
        return shopping(price, special, needs, memo);
    }

private:
    int shopping(vector<int> &price, vector<vector<int>> &special, vector<int> &needs, unordered_map<string, int> &memo)
    {
        // Serialize the needs vector as a string for memoization
        string key = serialize(needs);
        if (memo.count(key))
            return memo[key];

        // Calculate the cost without any special offers (base case)
        int res = 0;
        for (int i = 0; i < needs.size(); i++)
        {
            res += needs[i] * price[i]; // Calculate cost for remaining needs at regular price
        }
        // Try each special offer
        for (auto &s : special)
        {
            vector<int> clone = needs; // Copy current needs
            int j = 0;
            for (j = 0; j < needs.size(); ++j)
            {
                int diff = clone[j] - s[j];
                if (diff < 0) // Special offer cannot be used if it exceeds any need
                    break;
                clone[j] = diff; // Apply the offer
            }
            if (j == needs.size())
            {
                // If the special offer is valid, calculate the cost
                res = min(res, s.back() + shopping(price, special, clone, memo));
            }
        }

        // Memoize and return the result for this needs state
        memo[key] = res;
        return res;
    }

    // Helper function to serialize the needs vector as a string
    string serialize(vector<int> &needs)
    {
        string res;
        for (int n : needs)
        {
            res += to_string(n) + ",";
        }
        return res;
    }
};