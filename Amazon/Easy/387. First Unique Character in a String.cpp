/*
387. First Unique Character in a String

Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.


Example 1:

Input: s = "leetcode"

Output: 0

Explanation:

The character 'l' at index 0 is the first character that does not occur at any other index.

*/

// Approach - Using Hashmap -> char with count
// Traverse through string to find first unique ( count == 1 ) occurrence.

class Solution
{
public:
    int firstUniqChar(string s)
    {
        int n = s.length();
        unordered_map<char, int> freq;
        for (auto &ch : s)
        {
            freq[ch]++;
        }
        for (int i = 0; i < n; i++)
        {
            if (freq[s[i]] == 1)
                return i;
        }
        return -1;
    }
};