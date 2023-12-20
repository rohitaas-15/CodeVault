/*You are given a map of a labyrinth, and your task is to find a path from start to end. You can walk left, right, up and down.
Input
The first input line has two integers n and m: the height and width of the map.
Then there are n lines of m characters describing the labyrinth. Each character is . (floor), # (wall), A (start), or B (end). There is exactly one A and one B in the input.
Output
First print "YES", if there is a path, and "NO" otherwise.
If there is a path, print the length of the shortest such path and its description as a string consisting of characters L (left), R (right), U (up), and D (down). You can print any valid solution.
https://cses.fi/problemset/task/1193/*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl cout << endl

//-------------------------------------------------------------------------------
// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (!_nested)
        nl;
}
template <typename Complex>
void print(vector<Complex> &Vector)
{
    _nested = 1;
    for (Complex &C : Vector)
        print(C);
    nl;
    _nested = 0;
}
template <typename Complex, typename... ComplexObjects>
void print(Complex &&C, ComplexObjects &&...list)
{
    _nested = 1;
    print(C);
    _nested = 0;
    print(list...);
}

// scan helper
template <typename Primitive>
void scan(Primitive &P) { cin >> P; }
template <typename Complex>
void scan(vector<Complex> &Vector)
{
    for (Complex &C : Vector)
        scan(C);
}
template <typename Complex, typename... ComplexObjects>
void scan(Complex &C, ComplexObjects &...list)
{
    scan(C);
    scan(list...);
}

// fill bulk data
template <typename Primitive>
void fill(Primitive Value, Primitive &P) { P = Value; }
template <typename Primitive, typename Complex>
void fill(Primitive Value, vector<Complex> &Vector)
{
    for (Complex &C : Vector)
        fill(Value, C);
}
template <typename Primitive, typename Complex, typename... ComplexObjects>
void fill(Primitive Value, Complex &C, ComplexObjects &...list)
{
    fill(Value, C), fill(Value, list...);
}
//-------------------------------------------------------------------------------

const int N = 1e3 + 2;
char mat[N][N], direction[N][N];
int dis[N][N];

void solve()
{

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];

    int startx, starty, endx, endy;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 'A')
                startx = i, starty = j, mat[i][j] = '.';
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 'B')
                endx = i, endy = j, mat[i][j] = '.';

    memset(dis, -1, sizeof(dis));
    memset(direction, 'x', sizeof(direction));

    dis[startx][starty] = 0;
    queue<pair<int, int>> q;
    q.push({startx, starty});

    while (!q.empty())
    {
        auto node = q.front();
        q.pop();

        int x = node.first, y = node.second;

        int cnt = 0;
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if (abs(i) != abs(j))
                {
                    int nx = x + i, ny = y + j;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && dis[nx][ny] == -1 && mat[nx][ny] == '.')
                    {
                        dis[nx][ny] = dis[x][y] + 1;
                        q.push({nx, ny});

                        if (cnt == 0)
                            direction[nx][ny] = 'U';
                        if (cnt == 1)
                            direction[nx][ny] = 'L';
                        if (cnt == 2)
                            direction[nx][ny] = 'R';
                        if (cnt == 3)
                            direction[nx][ny] = 'D';
                    }
                    cnt++;
                }
    }

    if (dis[endx][endy] == -1)
    {
        print("NO");
        return;
    }
    print("YES");
    print(dis[endx][endy]);

    string path;

    while (direction[endx][endy] != 'x')
    {
        path.push_back(direction[endx][endy]);

        if (direction[endx][endy] == 'L')
        {
            endy++;
            continue;
        }
        if (direction[endx][endy] == 'D')
        {
            endx--;
            continue;
        }
        if (direction[endx][endy] == 'U')
        {
            endx++;
            continue;
        }
        if (direction[endx][endy] == 'R')
        {
            endy--;
            continue;
        }
    }
    reverse(all(path));
    print(path);
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int _t = 1;
    // cin >> _t;
    while (_t--)
        solve();
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line