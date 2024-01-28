

/*Given weights and values of N items, we need to put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
Note: Unlike 0/1 knapsack, you are allowed to break the item here. 
https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
*/
//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

struct Item
{
    int value;
    int weight;
};

// } Driver Code Ends
// class implemented
/*
struct Item{
    int value;
    int weight;
};
*/

double score(Item a)
{
    return (double)a.value / (double)a.weight;
}
bool compare(Item &a, Item &b)
{
    double ascore = score(a), bscore = score(b);
    return ascore > bscore;
}

class Solution
{
public:
    // Function to get the maximum total value in the knapsack.
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        vector<Item> v;
        for (int i = 0; i < n; i++)
        {
            v.push_back(arr[i]);
        }

        sort(v.begin(), v.end(), compare);

        double rem = (double)W;
        double ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (v[i].weight <= rem)
            {
                ans += (double)v[i].value;
                rem -= (double)v[i].weight;
            }
            else
            {
                double newVal = (double)v[i].value * ((double)rem / (double)v[i].weight);
                ans += newVal;
                break;
            }
        }

        return ans;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    // taking testcases
    cin >> t;
    cout << setprecision(6) << fixed;
    while (t--)
    {
        // size of array and weight
        int n, W;
        cin >> n >> W;

        Item arr[n];
        // value and weight of each item
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i].value >> arr[i].weight;
        }

        // function call
        Solution ob;
        cout << ob.fractionalKnapsack(W, arr, n) << endl;
    }
    return 0;
}
// } Driver Code Ends