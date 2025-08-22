#include<bits/stdc++.h>
using namespace std;

class Person {
    public:

    string id;
    unordered_map<string, int> net;

    Person() {}

    Person(string id) : id(id)
    {
        net.clear();
    }
};

class Transaction {
    public:

    string borrower, lender;
    int amount;

    Transaction() {}

    Transaction(string b, string l, int x) : borrower(b), lender(l), amount(x) {}
};

class Group {
    public:

    string id;
    unordered_map<string, Person> persons;
    vector<Transaction> transactions;

    Group() {}

    Group(string id, vector<string> pid) : id(id)
    {
        persons.clear();
        transactions.clear();
        for(string& p : pid)
        {
            persons[p] = Person(p);
        }
    }

    void addexpense(string b, string l, int amount)
    {
        persons[b].net[id] -= amount;
        persons[l].net[id] += amount;
        transactions.push_back(Transaction(b, l, amount));
        return;
    }

    void gettransaction()
    {
        cout << "Transactions for group " << id << ":" << endl;
        for(auto& transaction : transactions)
        {
            cout << "Person " << transaction.lender << " lent " << transaction.amount << " to person " << transaction.borrower << endl;
        }
        return;
    }

    void settleall()
    {
        priority_queue<pair<int, string>> max;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> min;
        for(auto& person : persons)
        {
            if(person.second.net[id] < 0)
            {
                min.push({person.second.net[id], person.first});
                person.second.net[id] = 0;
            }
            else if(person.second.net[id] > 0)
            {
                max.push({person.second.net[id], person.first});
                person.second.net[id] = 0;
            }
        }
        if(min.size() == 0 && max.size() == 0)
        {
            cout << "Already settled" << endl;
            return;
        }
        cout << "Settlement for group " << id << ":" << endl;
        while(!min.empty() && !max.empty())
        {
            string p1 = min.top().second, p2 = max.top().second;
            int a1 = abs(min.top().first), a2 = abs(max.top().first);
            min.pop();
            max.pop();
            if(a1 == a2)
            {
                cout << p1 << " -> " << a1 << " -> " << p2 << endl;
            }
            else if(a1 < a2)
            {
                cout << p1 << " -> " << a1 << " -> " << p2 << endl;
                max.push({a2-a1, p2});
            }
            else
            {
                cout << p1 << " -> " << a2 << " -> " << p2 << endl;
                min.push({(a1-a2) * (-1), p1});
            }
        }
        return;
    }

    void settle(string p1, string p2)
    {
        int& a1 = persons[p1].net[id];
        int& a2 = persons[p2].net[id];
        if(a1 < 0 && a2 > 0)
        {
            int x = min(-a1, a2);
            cout << p1 << " -> " << x << " -> " << p2 << endl;
            a1 += x;
            a2 -= x;
        }
        else if(a1 > 0 && a2 < 0)
        {
            int x = min(a1, -a2);
            cout << p2 << " -> " << x << " -> " << p1 << endl;
            a2 += x;
            a1 -= x;
        }
        else
        {
            cout << "Not possible between " << p1 << " and " << p2 << endl;
        }
        return;
    }
};

class Spliwise {
    public:

    unordered_map<string, Group> groups;

    Spliwise()
    {
        groups.clear();
    }

    void creategroup(string id, vector<string> pid)
    {
        groups[id] = Group(id, pid);
        cout << "Created group " << id << " with " << pid.size() << " persons" << endl;
        return;
    }

    void addexpense(string id, string b, string l, int amount)
    {
        groups[id].addexpense(b, l, amount);
        cout << "Added expense in group " << id << endl;
        return;
    }

    void gettransaction(string id)
    {
        groups[id].gettransaction();
        return;
    }

    void settleall(string id)
    {
        groups[id].settleall();
        return;
    }

    void settle(string id, string p1, string p2)
    {
        groups[id].settle(p1, p2);
        return;
    }
};

int main()
{
    string line;
    Spliwise splitwise;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "CREATEGROUP")
        {
            string id;
            int n;
            ss >> id >> n;
            vector<string> pid(n);
            for(int i=0; i<n; i++)
            {
                ss >> pid[i];
            }
            splitwise.creategroup(id, pid);
        }
        else if(command == "ADDEXPENSE")
        {
            string id, borrower, lender;
            int amount;
            ss >> id >> borrower >> lender >> amount;
            splitwise.addexpense(id, borrower, lender, amount);
        }
        else if(command == "GETTRANSACTIONS")
        {
            string id;
            ss >> id;
            splitwise.gettransaction(id);
        }
        else if(command == "SETTLEALL")
        {
            string id;
            ss >> id;
            splitwise.settleall(id);
        }
        else if(command == "SETTLE")
        {
            string id, p1, p2;
            ss >> id >> p1 >> p2;
            splitwise.settle(id, p1, p2);
        }
    }
}

// INPUT:

// CREATEGROUP G1 4 A B C D
// CREATEGROUP G2 4 C D E F
// ADDEXPENSE G1 A B 100
// ADDEXPENSE G1 B C 50
// ADDEXPENSE G1 D A 30
// ADDEXPENSE G2 E C 200
// ADDEXPENSE G2 F D 150
// ADDEXPENSE G2 C F 70
// GETTRANSACTIONS G1
// GETTRANSACTIONS G2
// SETTLEALL G1
// SETTLEALL G2
// SETTLEALL G1
// SETTLEALL G2

// OUTPUT:

// Created group G1 with 4 persons
// Created group G2 with 4 persons
// Added expense in group G1
// Added expense in group G1
// Added expense in group G1
// Added expense in group G2
// Added expense in group G2
// Added expense in group G2
// Transactions for group G1:
// Person B lent 100 to person A
// Person C lent 50 to person B
// Person A lent 30 to person D
// Transactions for group G2:
// Person C lent 200 to person E
// Person D lent 150 to person F
// Person F lent 70 to person C
// Settlement for group G1:
// A -> 50 -> C
// D -> 30 -> B
// A -> 20 -> B
// Settlement for group G2:
// E -> 150 -> D
// F -> 80 -> C
// E -> 50 -> C
// Already settled
// Already settled