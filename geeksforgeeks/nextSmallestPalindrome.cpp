
//Question - https://www.geeksforgeeks.org/given-a-number-find-next-smallest-palindrome-larger-than-this-number/#practice


//{ Driver Code Starts
#include <bits/stdc++.h>

using namespace std;

// } Driver Code Ends
//User function template for C++
class Solution{
public:
	vector<int> generateNextPalindrome(int num[], int n) {
	   if (n == 1) {
            int val = num[0];
            if (val < 9) {
                val++;
                vector < int > ans;
                ans.push_back(val);
                return ans;
            } else {
                vector < int > ans = {
                    1,
                    1
                };
                return ans;
            }
        }
        string s;
        for (int i = 0; i < n; i++) {
            s += (num[i] + 48);
        }
        bool ispal = true;
        for (int i = 0; i < n; i++) {
            if (s[i] != s[n - 1 - i]) {
                ispal = false;
                break;
            }
        }
        if (ispal) {
            int num = stoi(s, nullptr, 10);
            num++;
            s = to_string(num);
        }
        n = s.size();
        int sflag = 0;
        int uindex = -1;
        for (int i = (n + 1) / 2; i < n; i++) {
            if (s[n - 1 - i] < s[i]) {
                sflag = 1;
                if (uindex != -1) {
                    break;
                }
                for (int j = (n - 1) / 2; j >= 0; j--) {
                    if (s[j] != '9') {
                        s[j] = s[j] + 1;
                        break;
                    } else {
                        s[j] = '0';
                    }
                }
            } else if (s[n - 1 - i] > s[i]) {
                uindex = i;
            }
            if (sflag) {
                break;
            }
        }
        for (int i = (n + 1) / 2; i < n; i++) {
            s[i] = s[n - 1 - i];
        }
        vector < int > ans;
        for (auto i: s) {
            ans.push_back(i - 48);
        }
        return ans;

    }
	    
	    

};

//{ Driver Code Starts.


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int num[n];
        for (int i = 0; i < n; i++) {
            cin >> num[i];
        }
        Solution ob;
        auto ans = ob.generateNextPalindrome(num, n);
        for (auto x : ans) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}

// } Driver Code Ends
