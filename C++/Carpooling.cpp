#include<bits/stdc++.h>
using namespace std;

class Drive {
    public:
    string drivername;
    int seats;
    pair<double, double> start, end;
};

class Rider {
    public:
    string name;
    pair<double, double> start, end;

    double distance(Drive& d)
    {
        return sqrt((d.start.first - start.first) * (d.start.first - start.first) + (d.start.second - start.second) * (d.start.second - start.second)) * 111;
    }
    
    vector<int> availablerides(vector<Drive>& rides, Rider& r)
    {
        vector<int> result;
        for(int i=0; i<rides.size(); i++)
        {
            if(rides[i].seats > 0 && r.distance(rides[i]) <= 5.00)
            {
                result.push_back(i);
            }
        }
        return result;
    }
};

int main()
{
    string line;
    vector<Drive> rides;
    unordered_map<string, Rider> riders;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "MAKERIDE")
        {
            string name;
            int seats;
            double startlat, startlong, endlat, endlong;
            ss >> name >> seats >> startlat >> startlong >> endlat >> endlong;
            Drive d;
            d.drivername = name;
            d.seats = seats;
            d.start = {startlat, startlong};
            d.end = {endlat, endlong};
            rides.push_back(d);
            cout << "generated ride_id: " << rides.size() << endl;
        }
        else if(command == "GETRIDE")
        {
            string name;
            double startlat, startlong, endlat, endlong;
            ss >> name >> startlat >> startlong >> endlat >> endlong;
            Rider r;
            r.name = name;
            r.start = {startlat, startlong};
            r.end = {endlat, endlong};
            riders[name] = r;
            vector<int> available = r.availablerides(rides, r);
            if(!available.empty())
            {
                cout << "Available rides: " << endl;
                for(int a : available)
                {
                    cout << "ride_id: " << a << " driver: " << rides[a].drivername << " seats: " << rides[a].seats << " distance: " << r.distance(rides[a]) << endl;
                }
            }
        }
        else if(command == "TAKERIDE")
        {
            string name;
            int id;
            ss >> name >> id;
            vector<int> available = riders[name].availablerides(rides, riders[name]);
            if(find(available.begin(), available.end(), id-1) != available.end())
            {
                cout << "CONFIRMED" << endl;
                rides[id-1].seats--;
                riders.erase(name);
            }
            else
            {
                cout << "FAILURE" << endl;
            }
        }
    }
}

// INPUT:

// MAKERIDE John 2 12.90 77.50 12.95 77.60
// MAKERIDE Mary 1 12.92 77.52 12.96 77.62
// GETRIDE Alice 12.91 77.51 12.97 77.63
// TAKERIDE Alice 1
// GETRIDE Bob 12.905 77.505 12.97 77.61
// TAKERIDE Bob 1
// GETRIDE Charlie 12.91 77.52 12.97 77.65
// TAKERIDE Charlie 1
// TAKERIDE Charlie 2

// OUTPUT:

// generated ride_id: 1
// generated ride_id: 2
// Available rides:
// ride_id: 0 driver: John seats: 2 distance: 1.56978
// ride_id: 1 driver: Mary seats: 1 distance: 1.56978
// CONFIRMED
// Available rides:
// ride_id: 0 driver: John seats: 1 distance: 0.784889
// ride_id: 1 driver: Mary seats: 1 distance: 2.35467
// CONFIRMED
// Available rides:
// ride_id: 1 driver: Mary seats: 1 distance: 1.11
// FAILURE
// CONFIRMED