/*You and some monsters are in a labyrinth. When taking a step to some direction in the labyrinth, each monster may simultaneously take one as well. Your goal is to reach one of the boundary squares without ever sharing a square with a monster.
Your task is to find out if your goal is possible, and if it is, print a path that you can follow. Your plan has to work in any situation; even if the monsters know your path beforehand.
Input
The first input line has two integers n and m: the height and width of the map.
After this there are n lines of m characters describing the map. Each character is . (floor), # (wall), A (start), or M (monster). There is exactly one A in the input.
Output
First print "YES" if your goal is possible, and "NO" otherwise.
If your goal is possible, also print an example of a valid path (the length of the path and its description using characters D, U, L, and R). You can print any path, as long as its length is at most n \cdot m steps.
Constraints

1 \le n,m \le 1000
https://cses.fi/problemset/task/1194/*/
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
int n, m;
int monsterDis[N][N], myDis[N][N];
pair<int, int> par[N][N];
char dir[N][N];

void solve()
{
    memset(monsterDis, -1, sizeof(monsterDis));
    memset(myDis, -1, sizeof(myDis));
    memset(dir, 'x', sizeof(dir));

    cin >> n >> m;
    vector<vector<char>> mat(n, vector<char>(m));
    scan(mat);

    queue<pair<int, int>> q;
    int sx, sy;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 'M')
            {
                q.push({i, j});
                monsterDis[i][j] = 0;
                mat[i][j] = '.';
            }
            else if (mat[i][j] == 'A')
            {
                sx = i, sy = j;
                mat[i][j] = '.';
            }
        }

    while (!q.empty())
    {
        auto node = q.front();
        q.pop();

        int x = node.first, y = node.second;

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if (abs(i) != abs(j))
                {
                    int nx = x + i, ny = y + j;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && mat[nx][ny] == '.' && monsterDis[nx][ny] == -1)
                    {
                        monsterDis[nx][ny] = monsterDis[x][y] + 1;
                        q.push({nx, ny});
                    }
                }
    }

    q.push({sx, sy});
    myDis[sx][sy] = 0;

    vector<char> direction(4);
    direction[0] = 'U', direction[1] = 'L', direction[2] = 'R', direction[3] = 'D';

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
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && mat[nx][ny] == '.' && myDis[nx][ny] == -1)
                    {
                        myDis[nx][ny] = myDis[x][y] + 1;
                        par[nx][ny] = {x, y};
                        dir[nx][ny] = direction[cnt];
                        q.push({nx, ny});
                    }
                    cnt++;
                }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
            {
                if (myDis[i][j] != -1 && (monsterDis[i][j] == -1 || myDis[i][j] < monsterDis[i][j]))
                {
                    print("YES");
                    string path;
                    while (i != sx || j != sy)
                    {
                        path.push_back(dir[i][j]);
                        int store = i;
                        i = par[i][j].first, j = par[store][j].second;
                    }
                    reverse(all(path)), print(path.size()), print(path), exit(0);
                }
            }

    print("NO");
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