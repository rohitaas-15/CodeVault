#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 2;

class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();

        vector<int> hBIT(N, 0), lBIT(N, 0);

        // Function to update the BIT
        function<void(int, int, vector<int>&)> update = [&](int index, int value, vector<int>& BIT) {
            while (index < N) {
                BIT[index] += value;
                index += index & -index;
            }
        };

        // Function to query the BIT
        function<int(int, vector<int>&)> query = [&](int index, vector<int>& BIT) {
            int ans = 0;
            while (index > 0) {
                ans += BIT[index];
                index -= index & -index;
            }
            return ans;
        };

        // Function to count valid triplets with lBIT and hBIT
        function<int(vector<int>, vector<int>)> getTriplets = [&](vector<int> lBIT, vector<int> hBIT) {
            int ans = 0;
            for (int i = 0; i < n; i++) {
                update(rating[i], 1, hBIT);
            }

            for (int i = 0; i < n; i++) { // Consider i as the middle element
                update(rating[i], -1, hBIT);

                int lower = query(rating[i] - 1, lBIT);
                int higher = (n - i - 1) - query(rating[i], hBIT);

                ans += lower * higher;

                update(rating[i], 1, lBIT);
            }
            return ans;
        };

        int ans = getTriplets(lBIT, hBIT);

        // Reverse the ratings and count the triplets again
        reverse(rating.begin(), rating.end());

        ans += getTriplets(lBIT, hBIT);
        return ans;
    }
};
