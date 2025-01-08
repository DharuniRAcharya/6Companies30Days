/*
168. Excel Sheet Column Title

Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...



Example 1:

Input: columnNumber = 1
Output: "A"

Example 2:

Input: columnNumber = 28
Output: "AB"

Example 3:

Input: columnNumber = 701
Output: "ZY"

*/

/*
TC = O(logN)

The number of operations would be equal to the number of while loop iterations. In each iteration, the number N gets divided by 26. Hence the time complexity would be O(log26​N). Note that the base of the logarithm is not relevant when it comes to big O, since all logarithms are related by a constant factor.

SC = O(1)
*/

class Solution
{
public:
    string convertToTitle(int columnNumber)
    {
        string ans;
        while (columnNumber--)
        {
            ans += (char)((columnNumber) % 26 + 'A');
            columnNumber = (columnNumber) / 26;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};