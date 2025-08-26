#include<bits/stdc++.h>
using namespace std;

vector<string> actions {"WITHDRAW", "DEPOSIT", "ATMRESTORE"};

enum ACTION {
    WITHDRAW,
    DEPOSIT,
    ATMRESTORE
};

class Transaction {
    public:

    string customerid, atmid;
    ACTION action;
    int id, amount;

    Transaction(int id, string customerid, ACTION action, int amount, string atmid = "") : id(id), customerid(customerid), action(action), amount(amount), atmid(atmid) {}
};

class Customer {
    public:

    string id, password;
    vector<Transaction> transactions;
    int balance;

    Customer(string id = "", string password = "") : id(id), password(password), balance(0) {}

    bool authenticate(string pswd)
    {
        return pswd == password;
    }

    void changepswd(string pswd)
    {
        password = pswd;
        return;
    }
};

class ATM {
    public:

    string id;
    int balance;
    vector<Transaction> transactions;

    ATM() {}

    ATM(string id) : id(id), balance(0)
    {
        transactions.clear();
    }
};

class Bank {
    public:

    string id;
    unordered_map<string, Customer> customers;
    unordered_map<string, ATM> atms;
    vector<Transaction> transactions;

    Bank() {}

    void createcustomer(string id, string password)
    {
        if(customers.count(id))
        {
            cout << "Customer " << id << " already exists" << endl;
            return;
        }
        customers[id] = Customer(id, password);
        cout << "Customer " << id << " created" << endl;
        return;
    }

    void changepswd(string id, string pswd, string newpswd)
    {
        if(!customers.count(id))
        {
            cout << "Customer " << id << " does not exist" << endl;
            return;
        }
        bool flag = customers[id].authenticate(pswd);
        if(flag)
        {
            customers[id].changepswd(newpswd);
            cout << "Password changed for customer " << id << endl;
            return;
        }
        cout << "Wrong password" << endl;
        return;
    }

    void createatm(string id)
    {
        if(atms.count(id))
        {
            cout << "ATM " << id << " already exists" << endl;
            return;
        }
        atms[id] = ATM(id);
        cout << "ATM " << id << " created" << endl;
        return;
    }

    void addmoney(string id, int amount)
    {
        if(!atms.count(id))
        {
            cout << "ATM " << id << " does not exist" << endl;
            return;
        }
        int tid = transactions.size();
        Transaction transaction = Transaction(tid, "", ATMRESTORE, amount, id);
        transactions.push_back(transaction);
        atms[id].transactions.push_back(transaction);
        atms[id].balance += amount;
        cout << "Added " << amount << " in atm " << id << endl;
        return;
    }

    void deposit(string id, string pswd, int amount)
    {
        if(!customers[id].authenticate(pswd))
        {
            cout << "Wrong password" << endl;
            return;
        }
        int tid = transactions.size();
        Transaction transaction = Transaction(tid, id, DEPOSIT, amount, "");
        transactions.push_back(transaction);
        customers[id].transactions.push_back(transaction);
        customers[id].balance += amount;
        cout << "Added " << amount << " in " << id << "\'s account" << endl;
        return;
    }

    void withdraw(string id, string atmid, string pswd, int amount)
    {
        if(!customers[id].authenticate(pswd))
        {
            cout << "Wrong password" << endl;
            return;
        }
        if(atms[atmid].balance < amount)
        {
            cout << "Not enough money in atm " << atmid << endl;
            return;
        }
        if(customers[id].balance < amount)
        {
            cout << "Not enough money in " << id << "\'s account" << endl;
            return;
        }
        int tid = transactions.size();
        Transaction transaction = Transaction(tid, id, WITHDRAW, amount, atmid);
        transactions.push_back(transaction);
        customers[id].balance -= amount;
        customers[id].transactions.push_back(transaction);
        atms[atmid].balance -= amount;
        atms[atmid].transactions.push_back(transaction);
        cout << "Withdrew " << amount << " from " << id << "\'s account from atm " << atmid << endl;
        return;
    }

    void userrecord(string id, string pswd)
    {
        if(!customers[id].authenticate(pswd))
        {
            cout << "Wrong password" << endl;
            return;
        }
        if(customers[id].transactions.empty())
        {
            cout << "No transactions for customer " << id << endl;
            return;
        }
        cout << "Transactions for customer " << id << ":" << endl;
        for(auto& transaction : customers[id].transactions)
        {
            cout << "Transaction id: " << transaction.id << " ACTION: " << actions[transaction.action] << " amount: " << transaction.amount;
            if(!transaction.atmid.empty())
            {
                cout << " ATM id: " << transaction.atmid;
            }
            cout << endl;
        }
        return;
    }

    void atmrecord(string id)
    {
        if(atms[id].transactions.empty())
        {
            cout << "No transactions for ATM " << id << endl;
            return;
        }
        cout << "Transactions for ATM " << id << ":" << endl;
        for(auto& transaction : atms[id].transactions)
        {
            cout << "Transaction id: " << transaction.id << " action: " << actions[transaction.action];
            if(transaction.action == WITHDRAW)
            {
                cout << " customer id: " << transaction.customerid;
            }
            cout << " amount: " << transaction.amount << endl;
        }
        return;
    }

    void atmbalance(string id)
    {
        cout << atms[id].balance << endl;
        return;
    }

    void userbalance(string id, string pswd)
    {
        if(!customers[id].authenticate(pswd))
        {
            cout << "Wrong password" << endl;
            return;
        }
        cout << customers[id].balance << endl;
        return;
    }
};

int main()
{
    string line;
    Bank bank;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "CREATECUSTOMER")
        {
            string id, password;
            ss >> id >> password;
            bank.createcustomer(id, password);
        }
        else if(command == "CREATEATM")
        {
            string id;
            ss >> id;
            bank.createatm(id);
        }
        else if(command == "CHANGEPASSWORD")
        {
            string id, password, newp;
            ss >> id >> password >> newp;
            bank.changepswd(id, password, newp);
        }
        else if(command == "ADDMONEY")
        {
            string id;
            int amount;
            ss >> id >> amount;
            bank.addmoney(id, amount);
        }
        else if(command == "DEPOSIT")
        {
            string id, password;
            int amount;
            ss >> id >> password >> amount;
            bank.deposit(id, password, amount);
        }
        else if(command == "WITHDRAW")
        {
            string id, atmid, password;
            int amount;
            ss >> id >> atmid >> password >> amount;
            bank.withdraw(id, atmid, password, amount);
        }
        else if(command == "USERRECORD")
        {
            string id, password;
            ss >> id >> password;
            bank.userrecord(id, password);
        }
        else if(command == "ATMRECORD")
        {
            string id;
            ss >> id;
            bank.atmrecord(id);
        }
        else if(command == "ATMBALANCE")
        {
            string id;
            ss >> id;
            bank.atmbalance(id);
        }
        else if(command == "USERBALANCE")
        {
            string id, password;
            ss >> id >> password;
            bank.userbalance(id, password);
        }
    }
}

// INPUT:

// CREATECUSTOMER C1 pass1
// CREATECUSTOMER C2 pass2
// CREATECUSTOMER C1 pass3
// CHANGEPASSWORD C1 pass1 newpass
// CHANGEPASSWORD C2 wrong newpass
// CREATEATM A1
// CREATEATM A2
// CREATEATM A1
// ADDMONEY A1 1000
// ADDMONEY A2 500
// ADDMONEY A3 200
// DEPOSIT C1 newpass 300
// DEPOSIT C2 pass2 200
// DEPOSIT C2 wrong 100
// WITHDRAW C1 A1 newpass 100
// WITHDRAW C1 A1 wrong 50
// WITHDRAW C2 A1 pass2 600
// WITHDRAW C2 A2 pass2 100
// USERRECORD C1 newpass
// USERRECORD C2 pass2
// ATMRECORD A1
// ATMRECORD A2
// ATMBALANCE A1
// ATMBALANCE A2
// USERBALANCE C1 newpass
// USERBALANCE C2 pass2

// OUTPUT:

// Customer C1 created
// Customer C2 created
// Customer C1 already exists
// Password changed for customer C1
// Wrong password
// ATM A1 created
// ATM A2 created
// ATM A1 already exists
// Added 1000 in atm A1
// Added 500 in atm A2
// ATM A3 does not exist
// Added 300 in C1's account
// Added 200 in C2's account
// Wrong password
// Withdrew 100 from C1's account from atm A1
// Wrong password
// Not enough money in C2's account
// Withdrew 100 from C2's account from atm A2
// Transactions for customer C1:
// Transaction id: 2 ACTION: DEPOSIT amount: 300
// Transaction id: 4 ACTION: WITHDRAW amount: 100 ATM id: A1
// Transactions for customer C2:
// Transaction id: 3 ACTION: DEPOSIT amount: 200
// Transaction id: 5 ACTION: WITHDRAW amount: 100 ATM id: A2
// Transactions for ATM A1:
// Transaction id: 0 action: ATMRESTORE amount: 1000
// Transaction id: 4 action: WITHDRAW customer id: C1 amount: 100
// Transactions for ATM A2:
// Transaction id: 1 action: ATMRESTORE amount: 500
// Transaction id: 5 action: WITHDRAW customer id: C2 amount: 100
// 900
// 400
// 200
// 100