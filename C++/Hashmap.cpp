#include<bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    int count;
    Node* next;

    Node(int val) : val(val), count(1), next(nullptr) {}
};

class Hashmap {
    public:

    int SIZE = 100003;
    vector<Node*> table;

    int hashfunction(int key)
    {
        return key % SIZE;
    }

    public:

    Hashmap() : table(SIZE, nullptr) {}

    void put(int key)
    {
        int index = hashfunction(key);
        Node* head = table[index];
        Node* current = head;
        while(current)
        {
            if(current && current->val == key)
            {
                current->count++;
                cout << "Key already exists. Incremented count to " << current->count << endl;
                return;
            }
            current = current->next;
        }
        Node* newnode = new Node(key);
        newnode->next = head;
        table[index] = newnode;
        cout << "Inserted key " << key << " with count 1" << endl;
        return;
    }

    bool check(int key)
    {
        int index = hashfunction(key);
        Node* head = table[index];
        Node* current = head;
        while(current)
        {
            if(current->val == key)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void get(int key)
    {
        if(check(key))
        {
            int index = hashfunction(key);
            Node* head = table[index];
            Node* current = head;
            while(current)
            {
                if(current->val == key)
                {
                    cout << "Key: " << key << " Count: " << current->count << endl;
                    return;
                }
                current = current->next;
            }
        }
        else
        {
            cout << "Key not found" << endl;
        }
        return;
    }

    void remove(int key)
    {
        if(check(key))
        {
            int index = hashfunction(key);
            Node* head = table[index];
            Node* current = head;
            Node* prev = nullptr;
            while(current)
            {
                if(current->val == key)
                {
                    if(prev)
                    {
                        prev->next = current->next;
                    }
                    else
                    {
                        table[index] = current->next;
                    }
                    delete current;
                    cout << "Key " << key << " removed" << endl;
                    return;
                }
                prev = current;
                current = current->next;

            }
        }
        else
        {
            cout << "Key not found" << endl;
        }
        return;
    }
};

int main()
{
    string line;
    Hashmap map;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "PUT")
        {
            int key;
            ss >> key;
            map.put(key);
        }
        else if(command == "CHECK")
        {
            int key;
            ss >> key;
            cout << (map.check(key) ? "YES" : "NO") << endl;
        }
        else if(command == "GET")
        {
            int key;
            ss >> key;
            map.get(key);
        }
        else if(command == "REMOVE")
        {
            int key;
            ss >> key;
            map.remove(key);
        }
    }
}

// INPUT:

// PUT 10
// PUT 20
// PUT 10
// GET 10
// GET 20
// GET 30
// CHECK 10
// CHECK 30
// REMOVE 10
// GET 10
// CHECK 10
// REMOVE 30
// PUT 15
// PUT 25
// PUT 35
// GET 15
// REMOVE 15
// GET 15

// OUTPUT:

// Inserted key 10 with count 1
// Inserted key 20 with count 1
// Key already exists. Incremented count to 2
// Key: 10 Count: 2
// Key: 20 Count: 1
// Key not found
// YES
// NO
// Key 10 removed
// Key not found
// NO
// Key not found
// Inserted key 15 with count 1
// Inserted key 25 with count 1
// Inserted key 35 with count 1
// Key: 15 Count: 1
// Key 15 removed
// Key not found