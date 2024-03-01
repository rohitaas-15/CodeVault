/*You are given 3 Integers ‘n’, ‘R’ & ‘r’ where ‘n’ is the number of plates,

‘R’ is the radius of the table, and ‘r’ is the radius of the ‘n’ plates. The task is to find out whether the given table has enough space to accommodate the given number of plates of radius ‘r’. Consider the table and plates to be round and no plate can be placed above any other.

Each plate must be completely inside the table and must touch the edge of the table. Of course, the plates must not intersect, but they can touch each other.

You have to return true if the table can accommodate the given number of plates else return false.
https://www.codingninjas.com/studio/problem-of-the-day/easy*/
#include <bits/stdc++.h>
bool countPlatesOnTable(int n, int R, int r)
{
    if (r > R)
        return false;
    if (r == R)
        return n == 1;
    return (asin((double)r / (double)(R - r))) * (double)n <= (double)acos(-1); //find the arc length on the circumference of the bigger circle, between 2 small circles
}