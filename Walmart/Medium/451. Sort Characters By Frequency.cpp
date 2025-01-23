/*
451. Sort Characters By Frequency
Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

Example 1:

Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Example 2:

Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.

*/

// unordered_map -> freq of char
// bucket sorting
/*
    Time: O(N), where N <= 5 * 10^5 is the length of string s.
    Space: O(N)
*/

class Solution
{
public:
    string frequencySort(string s)
    {
        unordered_map<char, int> mpp;
        int n = s.size();
        vector<vector<char>> bucket(n + 1);
        string res;
        for (auto &ch : s)
        {
            mpp[ch]++;
        }
        for (auto &it : mpp)
        {
            int c = it.first;
            int f = it.second;
            bucket[f].push_back(c);
        }
        for (int i = n; i >= 0; i--)
        {
            for (char c : bucket[i])
            {
                res.append(i, c);
            }
        }
        return res;
    }
};