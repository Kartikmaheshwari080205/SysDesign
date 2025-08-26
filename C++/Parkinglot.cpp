#include<bits/stdc++.h>
using namespace std;

class Vehicle {
    public:
    int type;
    string id;
    string ticket;

    Vehicle(int type, string id, string ticket) : type(type), id(id), ticket(ticket) {}
};

struct Spot {
    int type;
    int status;
    bool occupied;
    string vehicleid;
    string ticket;
};

class ParkingLot {
    private:
    int floors, rows, columns;
    vector<vector<vector<Spot>>> layout;
    unordered_map<string, tuple<int, int, int>> vehicletospots;
    unordered_map<string, tuple<int, int, int>> ticketstospots;

    public:
    ParkingLot(int floors, int rows, int columns) : floors(floors), rows(rows), columns(columns)
    {
        layout.resize(floors, vector<vector<Spot>>(rows, vector<Spot>(columns)));
    }

    void setspot(int floor, int row, int column, int type, int status)
    {
        layout[floor][row][column].type = type;
        layout[floor][row][column].status = status;
        layout[floor][row][column].occupied = false;
    }

    void printlayout()
    {
        for(int i=0; i<floors; i++)
        {
            cout << "Floor " << i + 1 << ":" << endl;
            for(int j=0; j<rows; j++)
            {
                for(int k=0; k<columns; k++)
                {
                    cout << layout[i][j][k].type << "-" << layout[i][j][k].status << " ";
                }
                cout << endl;
            }
            cout << "------------------------" << endl;
        }
    }

    void park(Vehicle & v)
    {
        for(int i=0; i<floors; i++)
        {
            for(int j=0; j<rows; j++)
            {
                for(int k=0; k<columns; k++)
                {
                    if(layout[i][j][k].type == v.type && layout[i][j][k].status == 1 && !layout[i][j][k].occupied)
                    {
                        layout[i][j][k].occupied = true;
                        layout[i][j][k].vehicleid = v.id;
                        layout[i][j][k].ticket = v.ticket;
                        vehicletospots[v.id] = make_tuple(i, j, k);
                        ticketstospots[v.ticket] = make_tuple(i, j, k);
                        cout << "Vehicle parked at Floor: " << i + 1 << ", Row: " << j + 1 << ", Column: " << k + 1 << endl;
                        return;
                    }
                }
            }
        }
        cout << "No available spot for vehicle type " << v.type << endl;
    }

    void find(string id)
    {
        if(vehicletospots.find(id) != vehicletospots.end())
        {
            tuple<int, int, int> spot = vehicletospots[id];
            cout << "Vehicle with vehicle_id " << id << " parked at floor: " << get<0>(spot) + 1 << ", row: " << get<1>(spot) + 1 << ", column: " << get<2>(spot) + 1 << endl;
        }
        else if(ticketstospots.find(id) != ticketstospots.end())
        {
            tuple<int, int, int> spot = ticketstospots[id];
            cout << "Vehicle with ticket_id " << id << " parked at floor: " << get<0>(spot) + 1 << ", row: " << get<1>(spot) + 1 << ", column: " << get<2>(spot) + 1 << endl;
        }
        else
        {
            cout << "Vehicle not found" << endl;
        }
    }

    void freespots(int floor, int type)
    {
        int count = 0;
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<columns; j++)
            {
                if(layout[floor][i][j].type == type && layout[floor][i][j].status == 1 && !layout[floor][i][j].occupied)
                {
                    count++;
                }
            }
        }
        cout << "Free spots for vehicle type " << type << " on floor " << floor + 1 << ": " << count << endl;
    }

    void removecar(string& s)
    {
        vector<int> dashpos;
        for(int i=0; i<s.size(); i++)
        {
            if(s[i] == '-')
            {
                dashpos.push_back(i);
            }
        }
        if(!dashpos.empty())
        {
            int floor = stoi(s.substr(0, dashpos[0])) - 1;
            int row = stoi(s.substr(dashpos[0] + 1, dashpos[1] - dashpos[0] - 1)) - 1;
            int column = stoi(s.substr(dashpos[1] + 1)) - 1;
            if(layout[floor][row][column].occupied)
            {
                string vehicleid = layout[floor][row][column].vehicleid;
                string ticket = layout[floor][row][column].ticket;
                layout[floor][row][column].occupied = false;
                layout[floor][row][column].vehicleid = "";
                layout[floor][row][column].ticket = "";
                vehicletospots.erase(vehicleid);
                ticketstospots.erase(ticket);
                cout << "Spot at Floor: " << floor + 1 << ", Row: " << row + 1 << ", Column: " << column + 1 << " is now free." << endl;
            }
        }
        else if(vehicletospots.find(s) != vehicletospots.end())
        {
            tuple<int, int, int> spot = vehicletospots[s];
            int floor = get<0>(spot), row = get<1>(spot), column = get<2>(spot);
            vehicletospots.erase(s);
            ticketstospots.erase(layout[floor][row][column].ticket);
            layout[floor][row][column].occupied = false;
            layout[floor][row][column].vehicleid = "";
            layout[floor][row][column].ticket = "";
            cout << "Vehicle with vehicle_id " << s << " removed from parking lot." << endl;
        }
        else if(ticketstospots.find(s) != ticketstospots.end())
        {
            tuple<int, int, int> spot = ticketstospots[s];
            int floor = get<0>(spot), row = get<1>(spot), column = get<2>(spot);
            ticketstospots.erase(s);
            vehicletospots.erase(layout[floor][row][column].vehicleid);
            layout[floor][row][column].occupied = false;
            layout[floor][row][column].vehicleid = "";
            layout[floor][row][column].ticket = "";
            cout << "Vehicle with ticket_id " << s << " removed from parking lot." << endl;
        }
    }
};

int main()
{
    int floors, rows, columns;
    cin >> floors >> rows >> columns;
    ParkingLot lot(floors, rows, columns);
    for(int i=0; i<floors; i++)
    {
        for(int j=0; j<rows; j++)
        {
            for(int k=0; k<columns; k++)
            {
                string s;
                cin >> s;
                int dashpos = s.find('-');
                int type = stoi(s.substr(0, dashpos));
                int status = stoi(s.substr(dashpos + 1));
                lot.setspot(i, j, k, type, status);
            }
        }
    }
    string line;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "PARK")
        {
            int type;
            string id;
            string ticket;
            ss >> type >> id >> ticket;
            Vehicle v(type, id, ticket);
            lot.park(v);
        }
        else if(command == "SEARCH")
        {
            string id;
            ss >> id;
            lot.find(id);
        }
        else if(command == "FREESPOTS")
        {
            int floor, type;
            ss >> floor >> type;
            lot.freespots(floor - 1, type);
        }
        else if(command == "REMOVE")
        {
            string s;
            ss >> s;
            lot.removecar(s);
        }
    }
}

// INPUT:

// 1 4 4
// 4-1 4-1 2-1 2-0
// 2-1 4-1 2-1 2-1
// 4-0 2-1 4-0 2-1
// 4-1 4-1 4-1 2-1
// PARK 4 bh234 tkt4534
// SEARCH bh234
// SEARCH tkt4534
// FREESPOTS 1 4
// REMOVE 1-1-1
// REMOVE bh234
// REMOVE tkt4534

// OUTPUT:

// Vehicle parked at Floor: 1, Row: 1, Column: 1
// Vehicle with vehicle_id bh234 parked at floor: 1, row: 1, column
// Vehicle with ticket_id tkt4534 parked at floor: 1, row: 1, column: 1
// Free spots for vehicle type 4 on floor 1: 5
// Spot at Floor: 1, Row: 1, Column: 1 is now free.
// Vehicle with vehicle_id bh234 removed from parking lot.
// Vehicle with ticket_id tkt4534 removed from parking lot.