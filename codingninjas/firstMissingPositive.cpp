/*You are given an array 'ARR' of integers of length N. Your task is to find the first missing positive integer in linear time and constant space. In other words, find the lowest positive integer that does not exist in the array. The array can have negative numbers as well.

For example, the input [3, 4, -1, 1] should give output 2 because it is the smallest positive number that is missing in the input array.
https://www.codingninjas.com/studio/problems/first-missing-positive_699946?interviewProblemRedirection=true*/
#include <bits/stdc++.h> 
int firstMissing(int arr[], int n)
{
    int forN = 0;
    int M = 2e5+2, N = 1e5; //store two values in 1 array index, arr[i]/M will store frequency of i, arr[i]%M will store actual arr[i]
    for(int i =0;i<n;i++)
    {
        arr[i]+=N;
    }
    for(int i =0;i<n;i++)
    {
        if(arr[i]%M>n+N || arr[i]%M<0+N)
        {
            continue;
        }
        else if(arr[i]%M==n+N)
        {
            forN+=M;
        }
        else
        {
            arr[arr[i]%M-N]+=M;
        }
    }

    for(int i =1;i<n;i++)
    {
        if(arr[i]/M==0)
        {
            return i;
        }
    }

    if(forN==0)
    {
        return n;
    }
    else
    {
        return n+1;
    }

}