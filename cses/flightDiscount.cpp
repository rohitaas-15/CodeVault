/*Your task is to find a minimum-price flight route from Syrjälä to Metsälä. You have one discount coupon, using which you can halve the price of any single flight during the route. However, you can only use the coupon once.
When you use the discount coupon for a flight whose price is x, its price becomes \lfloor x/2 \rfloor (it is rounded down to an integer).
Input
The first input line has two integers n and m: the number of cities and flight connections. The cities are numbered 1,2,\ldots,n. City 1 is Syrjälä, and city n is Metsälä.
After this there are m lines describing the flights. Each line has three integers a, b, and c: a flight begins at city a, ends at city b, and its price is c. Each flight is unidirectional.
You can assume that it is always possible to get from Syrjälä to Metsälä.
Output
Print one integer: the price of the cheapest route from Syrjälä to Metsälä.
Constraints

2 \le n \le 10^5
1 \le m \le 2 \cdot 10^5
1 \le a,b \le n
1 \le c \le 10^9
https://cses.fi/problemset/task/1195/*/
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

const int N = 1e5 + 2;
int n, m;
vector<int> maxInPath(N, 0);
vector<vector<vector<int>>> adj(N);
vector<vector<int>> dist(N, vector<int>(2, INF));

void solve()
{

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, w});
    }

    set<vector<int>> s;
    s.insert({0, 1, 0});
    dist[1][0] = dist[1][1] = 0;

    while (!s.empty())
    {
        auto node = *(s.begin());
        s.erase(node);
        int from = node[1];
        int usedCoupon = node[2];

        if(from==n)
        {
            break;
        }

        for (auto i : adj[from])
        {
            int to = i[0], w = i[1];
            int newDis = dist[from][usedCoupon] + w;
            int newMx = max(maxInPath[from], w);

            if (usedCoupon)
            {
                if (newDis < dist[to][1])
                {
                    s.erase({dist[to][1], to, 1});
                    dist[to][1] = newDis, maxInPath[to] = newMx;
                    s.insert({dist[to][1], to, 1});
                }
            }
            else
            {
                //check if current answer is better and update
                if (newDis < dist[to][0])
                {
                    s.erase({dist[to][0], to, 0});
                    dist[to][0] = newDis, maxInPath[to] = newMx;
                    s.insert({dist[to][0], to, 0});
                }

                if (newDis < dist[to][1])
                {
                    s.erase({dist[to][1], to, 1});
                    dist[to][0] = newDis, maxInPath[to] = newMx;
                    s.insert({dist[to][0], to, 0});
                }

                //use coupon and check
                newDis -= (newMx + 1) / 2;
                if (newDis < dist[to][1])
                {
                    s.erase({dist[to][1], to, 1});
                    dist[to][1] = newDis, maxInPath[to] = newMx;
                    s.insert({dist[to][1], to, 1});
                }
            }
        }
    }

    print(dist[n][1]);

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