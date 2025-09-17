#include<bits/stdc++.h>
using namespace std;

class Ride {
    public:
   
    int last;
    set<int>::iterator it;
    set<int> players;
   
    Ride() : last(0) {}
   
    void play(int time)
    {
        for(int i=0; i<time; i++)
        {
            players.insert(++last);
            if(players.size() == 1)
            {
                it = players.begin();
            }
            else if(players.size() % 2 == 1)
            {
                it++;
            }
        }
    }
   
    void stop()
    {
        int n = players.size();
        if(n <= 1)
        {
            cout << "Game cannot be played" << endl;
            return;
        }
        if(n > 1)
        {
            int lastperson = *players.rbegin();
            int middleperson = *it;
            players.erase(lastperson);
            it = players.erase(it);
            if(it != players.begin() && !players.empty())
            {
                it--;
            }
            cout << lastperson << " " << middleperson << endl;
        }
    }
   
    void getstate()
    {
        for(auto& e : players)
        {
            cout << e << " ";
        }
        cout << endl;
    }
};

int main()
{
    Ride ride;
    string line;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "PLAY")
        {
            int time;
            ss >> time;
            ride.play(time);
        }
        else if(command == "STOP")
        {
            ride.stop();
        }
        else if(command == "STATE")
        {
            ride.getstate();
        }
    }
}