/*
1765. Map of Highest Peak

You are given an integer matrix isWater of size m x n that represents a map of land and water cells.

    If isWater[i][j] == 0, cell (i, j) is a land cell.
    If isWater[i][j] == 1, cell (i, j) is a water cell.

You must assign each cell a height in a way that follows these rules:

    The height of each cell must be non-negative.
    If the cell is a water cell, its height must be 0.
    Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).

Find an assignment of heights such that the maximum height in the matrix is maximized.

Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.

Example 1:

Input: isWater = [[0,1],[0,0]]
Output: [[1,0],[2,1]]
Explanation: The image shows the assigned heights of each cell.
The blue cell is the water cell, and the green cells are the land cells.

*/
// Multi source BFS
// TC = O(m*n) + O(m*n)
// SC = O(m*n)

class Solution
{
public:
    typedef pair<int, int> P;
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        int m = isWater.size();
        int n = isWater[0].size();
        vector<vector<int>> height(m, vector<int>(n, -1));
        queue<P> q;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isWater[i][j] == 1)
                {
                    height[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        while (!q.empty())
        {
            int N = q.size();
            while (N--)
            {
                P cur = q.front();
                q.pop();
                int i = cur.first;
                int j = cur.second;
                for (auto &dir : directions)
                {
                    int i_ = i + dir[0];
                    int j_ = j + dir[1];
                    if (i_ >= 0 && i_ < m && j_ >= 0 && j_ < n && height[i_][j_] == -1)
                    {
                        height[i_][j_] = height[i][j] + 1;
                        q.push({i_, j_});
                    }
                }
            }
        }
        return height;
    }
};