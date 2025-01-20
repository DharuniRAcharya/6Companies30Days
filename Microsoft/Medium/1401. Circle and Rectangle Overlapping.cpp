/*
1401. Circle and Rectangle Overlapping

You are given a circle represented as (radius, xCenter, yCenter) and an axis-aligned rectangle represented as (x1, y1, x2, y2), where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the rectangle.

Return true if the circle and rectangle are overlapped otherwise return false. In other words, check if there is any point (xi, yi) that belongs to the circle and the rectangle at the same time.



Example 1:

Input: radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
Output: true
Explanation: Circle and rectangle share the point (1,0).

*/

/*
Intuition
To determine whether a circle and a rectangle overlap, the goal is to check if any point on the rectangle also lies inside the circle. One way to approach this is by calculating the closest point on the rectangle to the center of the circle. If the distance between the circle's center and this point is less than or equal to the radius, then the circle and rectangle overlap.

Approach
    Find the closest point on the rectangle to the circle center:
        The x-coordinate of the closest point will be the x value between x1 (left edge) and x2 (right edge) that is nearest to xCenter (circle's center). This is calculated using max(x1, min(x2, xCenter)).
        Similarly, the y-coordinate of the closest point will be the y value between y1 (bottom edge) and y2 (top edge) that is nearest to yCenter. This is calculated using max(y1, min(y2, yCenter)).

    Check if the point is within the circle:

        Once the closest point (nearestX, nearestY) on the rectangle is found, calculate the squared Euclidean distance from this point to the circle's center (xCenter, yCenter). The formula for distance squared is:
        dist = (nearestX - xCenter)^2 + (nearestY - yCenter)^2
        If dist is less than or equal to the square of the radius (radius^2), then the circle and the rectangle overlap. Otherwise, they do not.
*/

// TC = O(1) SC = O(1)

class Solution
{
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2)
    {
        int nearestx = max(x1, min(x2, xCenter));
        int nearesty = max(y1, min(y2, yCenter));
        int dist = (nearestx - xCenter) * (nearestx - xCenter) + (nearesty - yCenter) * (nearesty - yCenter);
        if (dist <= radius * radius)
            return true;
        return false;
    }
};