#include<bits/stdc++.h>
using namespace std;

class Seat {
    public:

    int id;
    bool booked;

    Seat() {}
    Seat(int id) : id(id), booked(false) {}
};

class Flight {
    public:

    string id, from, to;
    int n;
    int empty;
    vector<Seat> seats;

    Flight() {}
    Flight(string id, int n, string from, string to) : id(id), n(n), empty(n), from(from), to(to)
    {
        for(int i=1; i<=n; i++)
        {
            seats.push_back(Seat(i));
        }
    }

    vector<int> findempty(int count)
    {
        vector<int> result;
        int i = 0;
        while(count > 0 && i < n)
        {
            if(!seats[i].booked)
            {
                result.push_back(seats[i].id);
                count--;
            }
            i++;
        }
        return result;
    }
};

class Booking {
    public:
    string pnr;
    int count;
    string flightid;
    vector<int> seatIds;

    Booking() {}
    Booking(string id, int count, string fid) : pnr(id), count(count), flightid(fid) {}
};

class Airport {
    public:
    unordered_map<string, Flight> flights;
    unordered_map<string, Booking> bookings;

    void addflight(string id, string from, string to, int capacity)
    {
        if(flights.count(id))
        {
            cout << "Flight " << id << " already exists" << endl;
            return;
        }
        flights[id] = Flight(id, capacity, from, to);
        cout << "Created flight " << id << " of capacity " << capacity << " from " << from << " to " << to << endl;
        return;
    }

    void searchbyid(string id)
    {
        if(!flights.count(id))
        {
            cout << "Flight " << id << " does not exist" << endl;
            return;
        }
        cout << "Flight: " << id << " From: " << flights[id].from << " To: " << flights[id].to << " Empty seats: " << flights[id].empty << endl;
        return;
    }
    void search(string from, string to)
    {
        bool flag = false;
        for(auto& f : flights)
        {
            Flight& flight = f.second;
            if(flight.from == from && flight.to == to)
            {
                flag = true;
                cout << "Flight: " << flight.id << " From: " << flight.from << " To: " << flight.to << " Empty seats: " << flight.empty << endl;
            }
        }
        if(!flag)
        {
            cout << "No flights found between " << from << " and " << to << endl;
        }
        return;
    }

    void book(string pnr, string fid, int count)
    {
        if(bookings.find(pnr) != bookings.end())
        {
            cout << "Booking with PNR " << pnr << " already exists" << endl;
            return;
        }
        if(flights.find(fid) == flights.end())
        {
            cout << "Flight " << fid << " does not exist" << endl;
            return;
        }
        Flight& flight = flights[fid];
        if(flight.empty < count)
        {
            cout << "Not enough seats available in flight " << fid << endl;
            return;
        }
        Booking booking(pnr, count, fid);
        vector<int> empty = flight.findempty(count);
        for(int e : empty)
        {
            flight.seats[e-1].booked = true;
            flight.empty--;
            booking.seatIds.push_back(e);
        }
        bookings[pnr] = booking;
        cout << "Booked " << count << " seats on flight " << fid << " with PNR " << pnr << endl;
    }

    void cancel(string pnr)
    {
        if(bookings.find(pnr) == bookings.end())
        {
            cout << "No booking with PNR " << pnr << endl;
            return;
        }
        Booking& booking = bookings[pnr];
        for(int sid : booking.seatIds)
        {
            flights[booking.flightid].seats[sid-1].booked = false;
            flights[booking.flightid].empty++;
        }
        cout << "Cancelled booking with PNR " << pnr << endl;
        bookings.erase(pnr);
    }

    void getdetails(string pnr)
    {
        if(bookings.find(pnr) == bookings.end())
        {
            cout << "No booking with PNR " << pnr << endl;
            return;
        }
        Booking& booking = bookings[pnr];
        cout << "Booking " << pnr << " on flight " << booking.flightid << " for " << booking.count << " seats: ";
        for(int sid : booking.seatIds)
        {
            cout << sid << " ";
        }
        cout << endl;
    }
};

int main()
{
    string line;
    Airport airport;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "ADDFLIGHT")
        {
            string id, from, to;
            int capacity;
            ss >> id >> from >> to >> capacity;
            airport.addflight(id, from, to, capacity);
        }
        else if(command == "SEARCHID")
        {
            string id;
            ss >> id;
            airport.searchbyid(id);
        }
        else if(command == "SEARCH")
        {
            string from, to;
            ss >> from >> to;
            airport.search(from, to);
        }
        else if(command == "BOOK")
        {
            string pnr, id;
            int count;
            ss >> pnr >> id >> count;
            airport.book(pnr, id, count);
        }
        else if(command == "CANCEL")
        {
            string pnr;
            ss >> pnr;
            airport.cancel(pnr);
        }
        else if(command == "GETDETAILS")
        {
            string pnr;
            ss >> pnr;
            airport.getdetails(pnr);
        }
    }
}

// INPUT:

// ADDFLIGHT F101 DEL BOM 5
// ADDFLIGHT F102 DEL BLR 3
// BOOK PNR001 F101 2
// BOOK PNR002 F101 2
// GETDETAILS PNR001
// SEARCHID F101
// CANCEL PNR001
// SEARCHID F101
// GETDETAILS PNR002
// BOOK PNR003 F102 3
// BOOK PNR004 F102 1
// GETDETAILS PNR003

// OUTPUT:

// Created flight F101 of capacity 5 from DEL to BOM
// Created flight F102 of capacity 3 from DEL to BLR
// Booked 2 seats on flight F101 with PNR PNR001
// Booked 2 seats on flight F101 with PNR PNR002
// Booking PNR001 on flight F101 for 2 seats: 1 2
// Flight: F101 From: DEL To: BOM Empty seats: 1
// Cancelled booking with PNR PNR001
// Flight: F101 From: DEL To: BOM Empty seats: 3
// Booking PNR002 on flight F101 for 2 seats: 3 4
// Booked 3 seats on flight F102 with PNR PNR003
// Not enough seats available in flight F102
// Booking PNR003 on flight F102 for 3 seats: 1 2 3