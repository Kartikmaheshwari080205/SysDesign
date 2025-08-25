#include<bits/stdc++.h>
using namespace std;

class Transaction {
    public:

    string itemid;
    int id, quantity;

    Transaction(int id, string iid, int quantity) : id(id), itemid(iid), quantity(quantity) {}
};

class Item {
    public:

    string id;
    int quantity;

    Item(string id = "", int quantity = 0) : id(id), quantity(quantity) {}
};

class VendingMachine {
    public:

    unordered_map<string, Item> items;
    vector<Transaction> transactions;

    VendingMachine()
    {
        items.clear();
    }

    void additem(string id, int quantity)
    {
        if(!items.count(id))
        {
            items[id] = Item(id, quantity);
        }
        else
        {
            items[id].quantity += quantity;
        }
        cout << "Added " << quantity << " of item " << id << endl;
        return;
    }

    void buy(string id, int quantity)
    {
        if(!items.count(id))
        {
            cout << "Item " << id << " does not exist" << endl;
            return;
        }
        if(items[id].quantity < quantity)
        {
            cout << "Not enough items available" << endl;
            return;
        }
        int tid = transactions.size();
        transactions.push_back(Transaction(tid, id, quantity));
        items[id].quantity -= quantity;
        cout << "Bought " << quantity << " of item " << id << endl;
        return;
    }

    void gettransactions()
    {
        if(transactions.empty())
        {
            cout << "No transactions yet" << endl;
            return;
        }
        for(auto& transaction : transactions)
        {
            cout << "Transaction id: " << transaction.id << " Item id: " << transaction.itemid << " Quantity: " << transaction.quantity << endl;
        }
        return;
    }

    void getquantity(string id)
    {
        if(!items.count(id))
        {
            cout << "Item " << id << " does not exist" << endl;
            return;
        }
        cout << "Quantity of item " << id << " left is " << items[id].quantity << endl;
        return;
    }

    void getstate()
    {
        bool flag = false;
        vector<string> outofstock;
        for(auto& item : items)
        {
            Item& i = item.second;
            if(i.quantity)
            {
                cout << "Item id: " << i.id << " Quantity: " << i.quantity << endl;
                flag = true;
            }
            else
            {
                outofstock.push_back(i.id);
            }
        }
        if(!flag)
        {
            cout << "No item left" << endl;
        }
        if(!outofstock.empty())
        {
            cout << "Out of stock items: ";
            for(auto& item : outofstock)
            {
                cout << item << " ";
            }
            cout << endl;
        }
        return;
    }
};

int main()
{
    string line;
    VendingMachine machine;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "ADDITEM")
        {
            string id;
            int quantity;
            ss >> id >> quantity;
            machine.additem(id, quantity);
        }
        else if(command == "BUY")
        {
            string id;
            int quantity;
            ss >> id >> quantity;
            machine.buy(id, quantity);
        }
        else if(command == "GETRECORD")
        {
            machine.gettransactions();
        }
        else if(command == "GETQUANTITY")
        {
            string id;
            ss >> id;
            machine.getquantity(id);
        }
        else if(command == "GETSTATE")
        {
            machine.getstate();
        }
    }
}

// INPUT:

// ADDITEM Coke 10
// ADDITEM Pepsi 5
// ADDITEM Chips 0
// ADDITEM Coke 5
// GETSTATE
// BUY Coke 3
// BUY Pepsi 2
// BUY Pepsi 5
// BUY Chips 1
// GETSTATE
// GETQUANTITY Coke
// GETQUANTITY Chips
// GETQUANTITY Water
// GETRECORD

// OUTPUT:

// Added 10 of item Coke
// Added 5 of item Pepsi
// Added 0 of item Chips
// Added 5 of item Coke
// Item id: Pepsi Quantity: 5
// Item id: Coke Quantity: 15
// Out of stock items: Chips
// Bought 3 of item Coke
// Bought 2 of item Pepsi
// Not enough items available
// Not enough items available
// Item id: Pepsi Quantity: 3
// Item id: Coke Quantity: 12
// Out of stock items: Chips
// Quantity of item Coke left is 12
// Quantity of item Chips left is 0
// Item Water does not exist
// Transaction id: 0 Item id: Coke Quantity: 3
// Transaction id: 1 Item id: Pepsi Quantity: 2