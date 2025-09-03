#include<bits/stdc++.h>
using namespace std;

class LRU {
    public:

    int cap, time;
    unordered_set<int> cache;
    unordered_map<int, int> last;

    LRU(int cap = 0) : cap(cap), time(0)
    {
        cache.clear();
        last.clear();
    }

    void put(int key)
    {
        if(cache.size() < cap)
        {
            cache.insert(key);
            last[key] = time++;
        }
        else
        {
            int remove, lastused = INT_MAX;
            for(auto& k : cache)
            {
                if(last[k] < lastused)
                {
                    lastused = last[k];
                    remove = k;
                }
            }
            cache.erase(remove);
            cache.insert(key);
            last[key] = time++;
            cout << "Removed key: " << remove << endl;
        }
        cout << "Inserted key: " << key << endl;
        return;
    }

    void get(int key)
    {
        if(cache.count(key))
        {
            cout << "Key " << key << " found" << endl;
        }
        else
        {
            cout << "Key " << key << " not found" << endl;
        }
        return;
    }

    void getstatus()
    {
        if(cache.empty())
        {
            cout << "Cache is empty" << endl;
            return;
        }
        cout << "Cache: ";
        for(auto& k : cache)
        {
            cout << k << " ";
        }
        cout << endl;
    }
};

int main()
{
    string line;
    LRU lru;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "INIT")
        {
            int cap;
            ss >> cap;
            lru = LRU(cap);
            cout << "Created cache of capacity " << cap << endl;
        }
        else if(command == "PUT")
        {
            int key;
            ss >> key;
            lru.put(key);
        }
        else if(command == "GET")
        {
            int key;
            ss >> key;
            lru.get(key);
        }
        else if(command == "STATE")
        {
            lru.getstatus();
        }
    }
}

// INPUT:

// INIT 2
// PUT 1
// PUT 2
// STATE
// GET 1
// STATE
// PUT 3
// STATE

// OUTPUT:

// Created cache of capacity 2
// Inserted key: 1
// Inserted key: 2
// Cache: 2 1
// Key 1 found
// Cache: 2 1
// Removed key: 1
// Inserted key: 3
// Cache: 3 2