/*https://leetcode.com/problems/reverse-pairs/



Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where:

0 <= i < j < nums.length and
nums[i] > 2 * nums[j].*/



ll merge(vector<int> &arr, ll s, ll e)
{
    ll mid = (s+e)/2;
    
    ll i = s,j=mid+1;
    ll cnt =0;
    vector<int> temp;
    
    while(i<=mid && j<=e)
    {
        if(arr[i]<=arr[j])
        {
            cnt+= lower_bound(arr.begin()+j, arr.begin()+e+1,arr[i]/2)-(arr.begin()+j);

            temp.push_back(arr[i++]);
            
        }
        else 
        {
            ll t = arr[j];


        
            cnt+= (arr.begin()+mid+1)-upper_bound(arr.begin()+i, arr.begin()+mid+1,2*t);


            temp.push_back(arr[j++]);
        }
    }
    
    while(i<=mid)
    {
        temp.push_back(arr[i++]);
    }
    
    while(j<=e)
    {
        temp.push_back(arr[j++]);
    }
    
    for(int i =0;i<temp.size();i++)
    {
        arr[s+i]=temp[i];
    }

    return cnt;
}



ll inv(vector<int> &arr, ll s, ll e)
{
    if(s>=e)
    {
        return 0;
    }
    
    int mid = (s+e)/2;
    
    ll left = inv(arr,s,mid);
    ll right = inv(arr,mid+1,e);
    
    ll cross = merge(arr,s,e);
    return left + right + cross;
}


int reversePairs(vector<int> &nums) {
    
 
    return inv(nums,0,nums.size()-1);
    
}
