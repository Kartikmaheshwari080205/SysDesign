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

    void size()
    {
        cout << s1.size() + s2.size() << endl;
        return;
    }

    void empty()
    {
        cout << (s1.empty() && s2.empty() ? "YES" : "NO") << endl;
        return;
    }

    void print()
    {
        if(s1.empty() && s2.empty())
        {
            cout << "Empty queue" << endl;
            return;
        }
        stack<int> temp1 = s1, temp2 = s2;
        cout << "Queue: ";
        while(!temp2.empty())
        {
            cout << temp2.top() << " ";
            temp2.pop();
        }
        while(!temp1.empty())
        {
            temp2.push(temp1.top());
            temp1.pop();
        }
        while(!temp2.empty())
        {
            cout << temp2.top() << " ";
            temp2.pop();
        }
        cout << endl;
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
        else if(command == "SIZE")
        {
            queue.size();
        }
        else if(command == "EMPTY")
        {
            queue.empty();
        }
        else if(command == "PRINT")
        {
            queue.print();
        }
    }
}

// INPUT:

// EMPTY
// INSERT 10
// INSERT 20
// INSERT 30
// SIZE
// PEEK
// PRINT
// REMOVE
// PRINT
// SIZE
// EMPTY
// REMOVE
// REMOVE
// REMOVE
// PEEK
// SIZE
// EMPTY
// PRINT

// OUTPUT:

// YES
// Inserted 10
// Inserted 20
// Inserted 30
// 3
// 10
// Queue: 10 20 30 
// Removed 10
// Queue: 20 30 
// 2
// NO
// Removed 20
// Removed 30
// -1
// -1
// 0
// YES
// Empty queue