#include<bits/stdc++.h>
using namespace std;

class Queue {
    private:

    stack<int> s1, s2;

    public:

    Queue() {}

    void insert(int key)
    {
        s1.push(key);
        cout << "Inserted " << key << endl;
        return;
    }

    void peek()
    {
        if(s1.empty() && s2.empty())
        {
            cout << -1 << endl;
            return;
        }
        if(s2.empty())
        {
            while(!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        cout << s2.top() << endl;
        return;
    }

    void remove()
    {
        if(s1.empty() && s2.empty())
        {
            cout << -1 << endl;
            return;
        }
        if(s2.empty())
        {
            while(!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        cout << "Removed " << s2.top() << endl;
        s2.pop();
        return;
    }
};

int main()
{
    string line;
    Queue queue;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "INSERT")
        {
            int key;
            ss >> key;
            queue.insert(key);
        }
        else if(command == "PEEK")
        {
            queue.peek();
        }
        else if(command == "REMOVE")
        {
            queue.remove();
        }
    }
}

// INPUT:

// INSERT 11
// INSERT 22
// PEEK
// REMOVE
// PEEK
// INSERT 33
// INSERT 44
// REMOVE
// REMOVE
// PEEK

// OUTPUT:

// Inserted 11
// Inserted 22
// 11
// Removed 11
// 22
// Inserted 33
// Inserted 44
// Removed 22
// Removed 33
// 44