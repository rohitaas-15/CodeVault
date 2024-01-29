/*Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:

You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
https://leetcode.com/problems/implement-queue-using-stacks/description/?envType=daily-question&envId=2024-01-29*/
#include <bits/stdc++.h>
using namespace std;
class MyQueue
{
public:
    stack<int> st1, st2;
    MyQueue()
    {
    }

    void push(int x)
    {
        st1.push(x);
    }

    int pop()
    {

        if (st2.size())
        {
            int ans = st2.top();
            st2.pop();
            return ans;
        }
        else
        {
            while (st1.size())
            {
                st2.push(st1.top());
                st1.pop();
            }
        }
        int ans = st2.top();
        st2.pop();
        return ans;
    }

    int peek()
    {

        if (st2.size())
        {
            return st2.top();
        }
        else
        {
            while (st1.size())
            {
                st2.push(st1.top());
                st1.pop();
            }
        }
        return st2.top();
    }

    bool empty()
    {
        return st1.empty() && st2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */