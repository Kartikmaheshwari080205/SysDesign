#include<bits/stdc++.h>
using namespace std;

class Meeting {
    public:

    int start, end;
    unordered_set<string> persons;

    Meeting(int s=0, int e=0, vector<string> pid = {}) : start(s), end(e)
    {
        for(auto p : pid)
        {
            persons.insert(p);
        }
    }
};

class Room {
    public:

    string id;
    vector<Meeting> meetings;

    Room(string id = "") : id(id) {}
};

class Scheduler {
    public:

    unordered_map<string, Room> rooms;

    Scheduler()
    {
        rooms.clear();
    }

    void addroom(string id)
    {
        rooms[id] = Room(id);
        cout << "Room " << id << " added" << endl;
    }

    bool overlap(int s1, int e1, int s2, int e2)
    {
        return max(s1, s2) < min(e1, e2);
    }

    void addmeeting(string id, int start, int end, vector<string> people)
    {
        for(auto& meeting : rooms[id].meetings)
        {
            if(overlap(meeting.start, meeting.end, start, end))
            {
                cout << "Meeting clash in romm " << id << endl;
                return;
            }
        }
        rooms[id].meetings.push_back(Meeting(start, end, people));
        cout << "Meeting added in room " << id << " from " << start << " to " << end << endl;
        return;
    }

    void getslots(string id)
    {
        auto& v = rooms[id].meetings;
        sort(v.begin(), v.end(), [](auto& a, auto& b){
            return a.start < b.start;
        });
        vector<pair<int, int>> result;
        int prev = 0;
        for(auto& meeting : v)
        {
            if(prev < meeting.start)
            {
                result.push_back({prev, meeting.start});
            }
            prev = max(prev, meeting.end);
        }
        if(prev < 24)
        {
            result.push_back({prev, 24});
        }
        if(result.empty())
        {
            cout << "No slots available in room " << id << endl;
            return;
        }
        cout << "Free slots: " << endl;
        for(auto& p : result)
        {
            cout << p.first << " to " << p.second << endl;
        }
        return;
    }

    void getavailability(string id)
    {
        vector<pair<int, int>> busy;
        for(auto& room : rooms)
        {
            Room& r = room.second;
            for(auto& meeting : r.meetings)
            {
                if(meeting.persons.count(id))
                {
                    busy.push_back({meeting.start, meeting.end});
                }
            }
        }
        if(busy.empty())
        {
            cout << "Free slots:" << endl << "0 to 24" << endl;
            return;
        }
        sort(busy.begin(), busy.end());
        vector<pair<int, int>> merged;
        merged.push_back(busy[0]);
        for(int i=1; i<busy.size(); i++)
        {
            if(busy[i].first <= merged.back().second)
            {
                merged.back().second = max(merged.back().second, busy[i].second);
            }
            else
            {
                merged.push_back(busy[i]);
            }
        }
        int prev = 0;
        cout << "Free slots:" << endl;
        for(auto& m : merged)
        {
            if(prev < m.first)
            {
                cout << prev << " to " << m.first << endl;
            }
            prev = max(prev, m.second);
        }
        if(prev < 24)
        {
            cout << prev << " to 24" << endl;
        }
        return;
    }
};

int main()
{
    string line;
    Scheduler scheduler;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "ADDROOM")
        {
            string id;
            ss >> id;
            scheduler.addroom(id);
        }
        else if(command == "ADDMEETING")
        {
            string id;
            int start, end;
            int n;
            ss >> id >> start >> end >> n;
            vector<string> people(n);
            for(int i=0; i<n; i++)
            {
                ss >> people[i];
            }
            scheduler.addmeeting(id, start, end, people);
        }
        else if(command == "GETSLOTS")
        {
            string id;
            ss >> id;
            scheduler.getslots(id);
        }
        else if(command == "GETAVAILABILITY")
        {
            string id;
            ss >> id;
            scheduler.getavailability(id);
        }
    }
}

// INPUT:

// ADDROOM R1
// ADDROOM R2
// ADDMEETING R1 9 11 2 Alice Bob
// ADDMEETING R2 10 12 1 Alice
// ADDMEETING R1 13 14 1 Bob
// GETSLOTS R1
// GETAVAILABILITY Alice
// GETAVAILABILITY Bob

// OUTPUT:

// Room R1 added
// Room R2 added
// Meeting added in room R1 from 9 to 11
// Meeting added in room R2 from 10 to 12
// Meeting added in room R1 from 13 to 14
// Free slots:
// 0 to 9
// 11 to 13
// 14 to 24
// Free slots:
// 0 to 9
// 12 to 24
// Free slots:
// 0 to 9
// 11 to 13
// 14 to 24