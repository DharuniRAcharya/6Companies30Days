/*
Number following a pattern

Given a pattern containing only I's and D's. I for increasing and D for decreasing. Devise an algorithm to print the minimum number following that pattern. Digits from 1-9 and digits can't repeat.

Example 1:

Input:
D
Output:
21
Explanation:
D is meant for decreasing, so we choose the minimum number among all possible numbers like 21,31,54,87,etc.
*/

// Approach
/*
Imagine you have some numbers, and you want to arrange them in a special way based on a pattern. The pattern can have two types of letters: 'I' and 'D'. 'I' means the next number should be bigger, and 'D' means the next number should be smaller.

The code you shared is like a magic spell that takes a pattern (a sequence of 'I's and 'D's) and then arranges the numbers in the smallest possible way according to that pattern.

Here's how the spell works:

    First, it creates a sequence of numbers from 1 to N+1, where N is the size of the pattern. N+1 because we're starting from 1.

    Then, it uses a special dance to arrange these numbers based on the pattern. If the pattern says 'D', it makes sure the next number is smaller, and if it says 'I', it makes sure the next number is bigger.

    It keeps dancing until it can't dance anymore, meaning it has arranged the numbers in the best possible way according to the pattern.

    Finally, it reveals the magic result, which is the smallest arrangement of numbers according to the given pattern.

Now, let's talk about time and space complexity.

Time Complexity: Imagine you have a big pile of blocks, and for each block, you need to decide whether to put it on top or below based on the pattern. The time it takes to do this dance is like how long it takes you to finish playing with all your blocks. So, the time complexity is O(N^2), which means it might take a bit of time if you have many blocks.

Space Complexity: Space is like how much room you need to play. In this case, the space needed is just for the sequence of numbers from 1 to N+1, so it's O(N).

So, the magic spell might take a bit of time if you have many blocks, but it doesn't need a lot of room to do its dance. And voila, the numbers are arranged just the way you wanted!
*/

class Solution
{
public:
    string printMinNumberForPattern(string S)
    {
        string res = "";
        for (int i = 1; i <= S.size() + 1; i++)
        {
            res += '0' + i;
        }
        while (true)
        {
            int j = 1, k = 0;
            bool flag = true;
            while (j < res.size())
            {
                if (S[k] == 'D' && res[j] > res[j - 1])
                {
                    swap(res[j], res[j - 1]);
                    flag = false;
                }
                if (S[k] == 'I' && res[j] < res[j - 1])
                {
                    swap(res[j], res[j - 1]);
                    flag = false;
                }
                j++;
                k++;
            }
            if (flag)
                break;
        }
        return res;
    }
};
