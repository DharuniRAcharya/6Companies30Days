/*
299. Bulls and Cows

You are playing the Bulls and Cows game with your friend.

You write down a secret number and ask your friend to guess what the number is. When your friend makes a guess, you provide a hint with the following info:

    The number of "bulls", which are digits in the guess that are in the correct position.
    The number of "cows", which are digits in the guess that are in your secret number but are located in the wrong position. Specifically, the non-bull digits in the guess that could be rearranged such that they become bulls.

Given the secret number secret and your friend's guess guess, return the hint for your friend's guess.

The hint should be formatted as "xAyB", where x is the number of bulls and y is the number of cows. Note that both secret and guess may contain duplicate digits.

Example 1:

Input: secret = "1807", guess = "7810"
Output: "1A3B"
Explanation: Bulls are connected with a '|' and cows are underlined:
"1807"
  |
"7810"

Example 2:

Input: secret = "1123", guess = "0111"
Output: "1A1B"
Explanation: Bulls are connected with a '|' and cows are underlined:
"1123"        "1123"
  |      or     |
"0111"        "0111"
Note that only one of the two unmatched 1s is counted as a cow since the non-bull digits can only be rearranged to allow one 1 to be a bull.

*/

// Approach - BULLS - CORRECT VALUE IN CORRECT POSITION & COWS - CORRECT VALUE IN WRONG POSITION
// calculate bulls first and calculate cows from remaining digits by maintaining remaining digits freq in secret and guess
// cows will be min of the digit freq in secret and guess (IGNORE BULLS) - handling duplicates of digits in bulls and cows
// TC = O(n) SC = O(20)

class Solution
{
public:
    string getHint(string secret, string guess)
    {
        int bull = 0, cow = 0;
        int n = secret.length();
        vector<int> secret_freq(10, 0), guess_freq(10, 0);
        string res;
        for (int i = 0; i < n; i++)
        {
            if (secret[i] == guess[i])
                bull++;
            else
            {
                secret_freq[secret[i] - '0']++;
                guess_freq[guess[i] - '0']++;
            }
        }
        for (int i = 0; i < 10; i++)
        {
            cow += min(secret_freq[i], guess_freq[i]);
        }
        res = to_string(bull) + 'A' + to_string(cow) + 'B';
        return res;
    }
};