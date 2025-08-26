#include<bits/stdc++.h>
using namespace std;

class Member {
    public:

    string id, name;
    
    Member(string id = "", string name = "") : id(id), name(name) {}
};

class Book {
    public:

    string id, name, author;
    int count, borrowed;
    queue<Member> reserved;

    Book(string id = "", string name = "", string author = "", int count = 0) : id(id), name(name), author(author), count(count), borrowed(0) {}
};

class Library {
    public:

    unordered_map<string, Book> books;
    unordered_map<string, Member> members;

    Library() {}

    void registeruser(string id, string name)
    {
        members[id] = Member(id, name);
        cout << "Member " << name << " registered with id " << id << endl;
        return;
    }

    void addbook(string id, string name, string author, int count)
    {
        if(books.count(id))
        {
            books[id].count += count;
        }
        else
        {
            books[id] = Book(id, name, author, count);
        }
        cout << "Added " << count << " copies of book " << name << endl;
        return;
    }

    void borrow(string mid, string bid)
    {
        if(!members.count(mid))
        {
            cout << "Member " << mid << " does not exist" << endl;
            return;
        }
        if(!books.count(bid))
        {
            cout << "Book " << bid << " does not exist" << endl;
            return;
        }
        Book& b = books[bid];
        if(b.count - b.borrowed <= 0)
        {
            cout << "Book not available at the moment" << endl;
            return;
        }
        if(b.count - b.borrowed - b.reserved.size() <= 0)
        {
            cout << "All copies are reserved" << endl;
            return;
        }
        cout << "Book " << bid << " issued to member " << members[mid].name << endl;
        b.borrowed++;
        return;
    }

    void returnbook(string mid, string bid)
    {
        Book& b = books[bid];
        b.borrowed--;
        cout << "Book " << bid << " returned by " << members[mid].name << endl;
        if(b.reserved.size() > 0)
        {
            b.borrowed++;
            cout << "Book " << bid << " issued to member " << b.reserved.front().name << endl;
            b.reserved.pop();
        }
        return;
    }

    void reserve(string mid, string bid)
    {
        books[bid].reserved.push(members[mid]);
        cout << "Book " << books[bid].name << " reserved by " << members[mid].name << endl;
        return;
    }

    void search(string name)
    {
        for(auto& book : books)
        {
            Book& b = book.second;
            if(b.name == name)
            {
                cout << "Found book " << name << " id " << b.id << " authored by " << b.author << endl;
                cout << "Total: " << b.count << " Available: " << b.count - b.borrowed - b.reserved.size() << endl;
                return;
            }
        }
        cout << "No book found with name: " << name << endl;
        return;
    }
};

int main()
{
    string line;
    Library library;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "REGISTER")
        {
            string id, name;
            ss >> id >> name;
            library.registeruser(id, name);
        }
        else if(command == "ADDBOOK")
        {
            string id, name, author;
            int count;
            ss >> id >> name >> author >> count;
            library.addbook(id, name, author, count);
        }
        else if(command == "BORROW")
        {
            string memberid, bookid;
            ss >> memberid >> bookid;
            library.borrow(memberid, bookid);
        }
        else if(command == "RETURN")
        {
            string memberid, bookid;
            ss >> memberid >> bookid;
            library.returnbook(memberid, bookid);
        }
        else if(command == "RESERVE")
        {
            string memberid, bookid;
            ss >> memberid >> bookid;
            library.reserve(memberid, bookid);
        }
        else if(command == "SEARCH")
        {
            string name;
            ss >> name;
            library.search(name);
        }
    }
}

// INPUT:

// REGISTER M1 Alice
// REGISTER M2 Bob
// REGISTER M3 Charlie
// REGISTER M4 Diana
// ADDBOOK B1 BookA AuthorX 2
// ADDBOOK B2 BookB AuthorY 1
// ADDBOOK B3 BookC AuthorZ 1
// BORROW M1 B1
// BORROW M2 B1
// BORROW M3 B1
// RESERVE M3 B1
// BORROW M4 B2
// RESERVE M2 B2
// BORROW M1 B3
// RETURN M1 B1
// RETURN M2 B1
// RETURN M4 B2
// SEARCH BookA

// OUTPUT:

// Member Alice registered with id M1
// Member Bob registered with id M2
// Member Charlie registered with id M3
// Member Diana registered with id M4
// Added 2 copies of book BookA
// Added 1 copies of book BookB
// Added 1 copies of book BookC
// Book B1 issued to member Alice
// Book B1 issued to member Bob
// Book not available at the moment
// Book BookA reserved by Charlie
// Book B2 issued to member Diana
// Book BookB reserved by Bob
// Book B3 issued to member Alice
// Book B1 returned by Alice
// Book B1 issued to member Charlie
// Book B1 returned by Bob
// Book B2 returned by Diana
// Book B2 issued to member Bob
// Found book BookA id B1 authored by AuthorX
// Total: 2 Available: 1