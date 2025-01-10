/*
1823. Find the Winner of the Circular Game

*/

class Solution
{
public:
    int findTheWinner(int n, int k)
    {
        int res = 0;
        for (int i = 1; i <= n; i++)
            res = (res + k) % i;
        return res + 1;
    }
};