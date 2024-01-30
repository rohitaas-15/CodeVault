/*You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

Evaluate the expression. Return an integer that represents the value of the expression.

Note that:

The valid operators are '+', '-', '*', and '/'.
Each operand may be an integer or another expression.
The division between two integers always truncates toward zero.
There will not be any division by zero.
The input represents a valid arithmetic expression in a reverse polish notation.
The answer and all the intermediate calculations can be represented in a 32-bit integer.
https://leetcode.com/problems/evaluate-reverse-polish-notation/description/?envType=daily-question&envId=2024-01-30*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int evalRPN(vector<string>& tokens) {

        stack<int> s;
        int i = 0;
        while(i<tokens.size())
        {
            if(!s.size())
            {
                s.push(stoi(tokens[i++],nullptr,10));
                continue;
            }

            if(tokens[i]=="+")
            {
                int cnt = 2;
                int op2= s.top();
                s.pop();
                int op1= s.top();
                s.pop();
                int result =op1+op2;
                s.push(result);
                i++;
                continue;
            }

            if(tokens[i]=="-")
            {
                int cnt = 2;
                int op2= s.top();
                s.pop();
                int op1= s.top();
                s.pop();
                int result =op1-op2;
                s.push(result);
                i++;
                continue;
            }

            if(tokens[i]=="/")
            {
                int cnt = 2;
                int op2= s.top();
                s.pop();
                int op1= s.top();
                s.pop();
                int result =op1/op2;
                s.push(result);
                i++;
                continue;
            }

            if(tokens[i]=="*")
            {
                int cnt = 2;
                int op2= s.top();
                s.pop();
                int op1= s.top();
                s.pop();
                int result =op1*op2;
                s.push(result);
                i++;
                continue;
            }
            s.push(stoi(tokens[i++],nullptr,10));
        }
        return s.top();
        
    }
};