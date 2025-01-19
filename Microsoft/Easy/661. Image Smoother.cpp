/*
661. Image Smoother

An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image by rounding down the average of the cell and the eight surrounding cells (i.e., the average of the nine cells in the blue smoother). If one or more of the surrounding cells of a cell is not present, we do not consider it in the average (i.e., the average of the four cells in the red smoother).
Given an m x n integer matrix img representing the grayscale of an image, return the image after applying the smoother on each cell of it.

Example 1:

Input: img = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[0,0,0],[0,0,0],[0,0,0]]
Explanation:
For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0

*/
// visit the neighbours -> using directions vector = {0,-1} {0, 1} {-1, 0} {1, 0}
// TC = O(n*m)
// SC = O(m*n) (using copy of img and updating values) => optimized to O(1) -> constraints img[i][j] <= 255 => 8 bits of 32 bit value Thus use remaining bits for storing updated value using left shift by 8 bits and return the updated value by right shift
// get the original value for computation -> img[i][j] mod 256

class Solution
{
public:
    vector<vector<int>> imageSmoother(vector<vector<int>> &img)
    {
        int rows = img.size();
        int cols = img[0].size();
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                int total = 0, cnt = 0;
                for (int i = r - 1; i <= r + 1; i++)
                {
                    for (int j = c - 1; j <= c + 1; j++)
                    {
                        if (i < 0 | i >= rows | j < 0 | j >= cols)
                            continue;
                        total += img[i][j] % 256;
                        cnt++;
                    }
                }
                img[r][c] = img[r][c] ^ total / cnt << 8;
            }
        }
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                img[r][c] = img[r][c] >> 8;
            }
        }
        return img;
    }
};