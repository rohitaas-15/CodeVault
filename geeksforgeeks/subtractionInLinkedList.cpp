//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// Node Class
class Node
{
public:
    int data;
    Node *next;

    Node(int val) : data(val), next(NULL) {}
};

// Linked List Class
class LinkedList
{
public:
    Node *head;
    Node *tail;

    LinkedList() : head(NULL), tail(NULL) {}

    // creates a new node with given value and appends it at the end of the linked list
    void insert(int val)
    {
        if (head == NULL)
        {
            head = new Node(val);
            tail = head;
        }
        else
        {
            tail->next = new Node(val);
            tail = tail->next;
        }
    }
};

// } Driver Code Ends
// User function Template for C++
vector<int> number;
void extractNumber(Node *head)
{
    if (head == NULL)
    {
        return;
    }

    number.push_back(head->data);
    extractNumber(head->next);
}

void removeZeroes(vector<int> &no1)
{
    while (no1.size() != 1 && no1[no1.size() - 1] == 0)
    {
        no1.pop_back();
    }
}

void makeNo1Smaller(vector<int> &no1, vector<int> &no2)
{

    if (no1.size() == no2.size())
    {
        reverse(no1.begin(), no1.end());
        reverse(no2.begin(), no2.end());

        if (no1 > no2)
        {
            swap(no1, no2);
        }

        reverse(no1.begin(), no1.end());
        reverse(no2.begin(), no2.end());
    }
    else if (no2.size() < no1.size())
    {
        swap(no1, no2);
    }

    while (no1.size() < no2.size())
    {
        no1.push_back(0);
    }
}

vector<int> ans;
void findCarry(int index, vector<int> &no2, vector<int> &no1)
{
    if (no2[index] != 0)
    {
        no2[index]--;
        return;
    }
    else
    {
        findCarry(index + 1, no2, no1);
        no2[index] = 9;
    }
}

void subtract(int index, vector<int> &no2, vector<int> &no1)
{
    if (index == no2.size())
    {
        return;
    }

    if (no2[index] < no1[index])
    {
        findCarry(index + 1, no2, no1);
        no2[index] += 10;
    }

    ans[index] = no2[index] - no1[index];
    subtract(index + 1, no2, no1);
}

Node *makeLinkedList(int index, vector<int> &ans)
{
    if (index == ans.size())
    {
        return NULL;
    }

    Node *temp = new Node(ans[index]);
    temp->next = makeLinkedList(index + 1, ans);
    return temp;
}

void cleanData(vector<int> &no1, vector<int> &no2)
{
    removeZeroes(no1);
    removeZeroes(no2);
    makeNo1Smaller(no1, no2);
}

class Solution
{
public:
    Node *subLinkedList(Node *head1, Node *head2)
    {
        number.clear();
        extractNumber(head1);
        auto no1 = number;
        number.clear();
        extractNumber(head2);
        auto no2 = number;

        reverse(no1.begin(), no1.end());
        reverse(no2.begin(), no2.end());

        cleanData(no1,no2);

        ans.clear();
        ans.resize(no2.size(), 0);
        subtract(0, no2, no1);

        removeZeroes(ans);
        reverse(ans.begin(), ans.end());
        return makeLinkedList(0, ans);
    }
};

//{ Driver Code Starts.

// prints the elements of linked list starting with head
void printList(Node *n)
{
    while (n)
    {
        cout << n->data;
        n = n->next;
    }
    cout << endl;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        int n;
        cin >> n;
        LinkedList LL1;
        string l1, l2;
        cin >> l1;
        for (int j = 0; j < n; ++j)
        {
            int x = (l1[j] - '0');
            LL1.insert(x);
        }

        int m;
        cin >> m;
        LinkedList LL2;
        cin >> l2;
        for (int j = 0; j < m; ++j)
        {
            int x = (l2[j] - '0');
            LL2.insert(x);
        }

        Solution ob;
        Node *res = ob.subLinkedList(LL1.head, LL2.head);
        printList(res);
    }

    return 0;
}

// } Driver Code Ends