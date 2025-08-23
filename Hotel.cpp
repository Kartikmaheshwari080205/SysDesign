#include<bits/stdc++.h>
using namespace std;

class Room {
    public:

    string id, type;
    int capacity;
    bool booked;

    Room() {}

    Room(string id, string type, int cap) : id(id), type(type), capacity(cap), booked(false) {}
};

class Booking {
    public:

    string id;
    int people;
    string roomid;

    Booking() {}

    Booking(string id, int p, string rid) : id(id), people(p), roomid(rid) {}
};

class Hotel {
    public:

    unordered_map<string, Booking> bookings;
    unordered_map<string, Room> rooms;

    Hotel()
    {
        rooms.clear();
    }

    void addroom(string id, string type, int capacity)
    {
        rooms[id] = Room(id, type, capacity);
        cout << "Added room " << id << " of type " << type << " with capacity " << capacity << endl;
        return;
    }

    void availabletype(string type)
    {
        vector<pair<string, int>> result;
        for(auto& room : rooms)
        {
            Room& r = room.second;
            if(r.type == type && r.booked == false)
            {
                result.push_back({r.id, r.capacity});
            }
        }
        if(result.empty())
        {
            cout << "No rooms found of type " << type << endl;
            return;
        }
        cout << "Available rooms:" << endl;
        for(auto& p : result)
        {
            cout << "Room id: " << p.first << " capacity: " << p.second << endl;
        }
        return;
    }

    void book(string bid, string type, int people)
    {
        string best = "";
        int mincap = INT_MAX;
        for(auto& room : rooms)
        {
            Room& r = room.second;
            if(r.type == type && r.capacity >= people && !r.booked)
            {
                if(r.capacity < mincap)
                {
                    best = r.id;
                    mincap = r.capacity;
                }
            }
        }
        if(!best.empty())
        {
            bookings[bid] = Booking(bid, people, best);
            rooms[best].booked = true;
            cout << "Booked room " << best << " of type " << type << " for booking " << bid << endl;
        }
        else
        {
            cout << "No empty rooms of type " << type << " available at the moment" << endl;
        }
        return;
    }

    void checkout(string id)
    {
        string rid = bookings[id].roomid;
        rooms[rid].booked = false;
        bookings.erase(id);
        cout << "Room " << rid << " is empty now" << endl;
        return;
    }
};

int main()
{
    string line;
    Hotel hotel;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "ADDROOM")
        {
            string id, type;
            int capacity;
            ss >> id >> type >> capacity;
            hotel.addroom(id, type, capacity);
        }
        else if(command == "SHOWAVAILABLE")
        {
            string type;
            ss >> type;
            hotel.availabletype(type);
        }
        else if(command == "BOOK")
        {
            string id, type;
            int people;
            ss >> id >> type >> people;
            hotel.book(id, type, people);
        }
        else if(command == "CHECKOUT")
        {
            string id;
            ss >> id;
            hotel.checkout(id);
        }
    }
}

// INPUT:

// ADDROOM R1 Deluxe 2
// ADDROOM R2 Deluxe 4
// ADDROOM R3 Standard 3
// SHOWAVAILABLE Deluxe
// BOOK B1 Deluxe 2
// BOOK B2 Deluxe 3
// SHOWAVAILABLE Deluxe
// BOOK B3 Deluxe 2
// CHECKOUT B1
// BOOK B4 Deluxe 2
// SHOWAVAILABLE Standard
// BOOK B5 Standard 4
// BOOK B6 Standard 2
// CHECKOUT B6
// SHOWAVAILABLE Standard

// OUTPUT:

// Added room R1 of type Deluxe with capacity 2
// Added room R2 of type Deluxe with capacity 4
// Added room R3 of type Standard with capacity 3
// Available rooms:
// Room id: R2 capacity: 4
// Room id: R1 capacity: 2
// Room R1 booked with booking id B1
// Room R2 booked with booking id B2
// No rooms found of type Deluxe
// No empty rooms of type Deluxe available at the moment
// Room R1 is empty now
// Room R1 booked with booking id B4
// Available rooms:
// Room id: R3 capacity: 3
// No empty rooms of type Standard available at the moment
// Room R3 booked with booking id B6
// Room R3 is empty now
// Available rooms:
// Room id: R3 capacity: 3