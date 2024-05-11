#include <bits/stdc++.h>
using namespace std;


bool compare(pair<int,int> &a, pair<int,int> &b)
{
    return a.first*b.second<b.first*a.second;
}
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        vector<pair<int,int> > fractions;
        int n = wage.size();
        for(int i = 0;i<n;i++)
        {
            fractions.push_back({wage[i],quality[i]});
        }
        sort(fractions.begin(),fractions.end(),compare); //sorting the workers on the basis
                                                        // of their minimum proportion constant
        double sum =0;
        priority_queue<double> pq; //taking the k minimum qualities to multiply with current worker's constant
        for(int i = 0;i<k;i++)
        {
            pq.push((double)fractions[i].second);
            sum+=(double)fractions[i].second;
        }
        double ans = (double)sum*((double)fractions[k-1].first/(double)fractions[k-1].second);
        for(int i = k;i<n;i++)
        {
            double remove = pq.top();
            pq.pop();
            sum-=remove;
            pq.push((double)fractions[i].second);
            sum+=fractions[i].second;
            ans = min(ans,(double)sum*((double)fractions[i].first/(double)fractions[i].second)); //assuming current worker's proportion
                                                                                                //constant will be maximum
        }
        return ans;
    }
};