#include<bits/stdc++.h>
using namespace std;


class Product {
    public:

    string id;
    int price;
    int count;

    Product(string id = "", int p=0, int c=0) : id(id), price(p), count(c) {}
};

class Seller {
    public:

    string id;
    unordered_set<string> paymentmethods;
    unordered_map<string, Product> products;
    unordered_set<string> pincodes;

    Seller() {}

    Seller(string id, vector<string> pm, vector<string> pc) : id(id)
    {
        paymentmethods.clear();
        pincodes.clear();
        for(string p : pm)
        {
            paymentmethods.insert(p);
        }
        for(string p : pc)
        {
            pincodes.insert(p);
        }
    }
};

class Inventory {
    public:

    unordered_map<string, Seller> sellers;

    Inventory() {}

    void createseller(string id, vector<string> pc, vector<string> pm)
    {
        sellers[id] = Seller(id, pm, pc);
        cout << "Seller " << id << " created" << endl;
        return;
    }

    void addinventory(string pid, string sid, int count)
    {
        sellers[sid].products[pid].count += count;
        cout << "Added " << count << " products " << pid << " to seller " << sid << endl;
        return;
    }

    void getinventory(string pid, string sid)
    {
        if(!sellers.count(sid))
        {
            cout << "Seller does not exist" << endl;
            return;
        }
        if(!sellers[sid].products.count(pid))
        {
            cout << "Product does not exist" << endl;
            return;
        }
        cout << sellers[sid].products[pid].count << endl;
        return;
    }

    void order(string orderid, string dest, string sid, string pid, int count, string method)
    {
        if(!sellers[sid].pincodes.count(dest))
        {
            cout << "Seller does not sell at destination " << dest << endl;
            return;
        }
        if(!sellers[sid].paymentmethods.count(method))
        {
            cout << "Seller does not accept " << method << endl;
            return;
        }
        if(!sellers[sid].products.count(pid))
        {
            cout << "Seller does not sell product " << pid << endl;
            return;
        }
        if(count > sellers[sid].products[pid].count)
        {
            cout << "Seller does not have " << count << " product " << pid << endl;
            return;
        }
        sellers[sid].products[pid].count -= count;
        cout << "Order placed of " << count << " " << pid << " from " << sid << " to " << dest << endl;
        return;
    }
};

int main()
{
    string line;
    Inventory inventory;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "CREATESELLER")
        {
            string id;
            int n, m;
            ss >> id >> n;
            vector<string> pincodes(n);
            for(int i=0; i<n; i++)
            {
                ss >> pincodes[i];
            }
            ss >> m;
            vector<string> payment(m);
            for(int i=0; i<m; i++)
            {
                ss >> payment[i];
            }
            inventory.createseller(id, pincodes, payment);
        }
        else if(command == "ADDINVENTORY")
        {
            string productid, sellerid;
            int count;
            ss >> productid >> sellerid >> count;
            inventory.addinventory(productid, sellerid, count);
        }
        else if(command == "GETINVENTORY")
        {
            string productid, sellerid;
            ss >> productid >> sellerid;
            inventory.getinventory(productid, sellerid);
        }
        else if(command == "ORDER")
        {
            string orderid, destination, sellerid, productid, payment;
            int count;
            ss >> orderid >> destination >> sellerid >> productid >> count >> payment;
            inventory.order(orderid, destination, sellerid, productid, count, payment);
        }
    }
}

// INPUT:

// CREATESELLER S1 3 110001 110002 110003 2 COD CARD
// CREATESELLER S2 2 560001 560002 1 UPI
// ADDINVENTORY P1 S1 10
// ADDINVENTORY P2 S1 5
// ADDINVENTORY P3 S2 20
// GETINVENTORY P1 S1
// GETINVENTORY P2 S1
// GETINVENTORY P3 S2
// GETINVENTORY P4 S1
// GETINVENTORY P1 S3
// ORDER O1 110001 S1 P1 3 COD
// ORDER O2 110004 S1 P1 2 CARD
// ORDER O3 110001 S1 P4 1 COD
// ORDER O4 560001 S2 P3 25 UPI
// ORDER O5 560002 S2 P3 5 CARD
// ORDER O6 560001 S2 P3 10 UPI

// OUTPUT:

// Seller S1 created
// Seller S2 created
// Added 10 products P1 to seller S1
// Added 5 products P2 to seller S1
// Added 20 products P3 to seller S2
// 10
// 5
// 20
// Product does not exist
// Seller does not exist
// Order placed of 3 P1 from S1 to 110001
// Seller does not sell at destination 110004
// Seller does not sell product P4
// Seller does not have 25 product P3
// Seller does not accept CARD
// Order placed of 10 P3 from S2 to 560001