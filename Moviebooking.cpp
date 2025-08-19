#include <bits/stdc++.h>
using namespace std;

class Seat {
public:
    int row, col;
    bool booked;

    Seat(int r, int c) : row(r), col(c), booked(false) {}
};

class Show {
public:
    int showid, movieid;
    int starttime, endtime;
    int r, c;
    int empty;
    vector<vector<Seat>> seats;
    unordered_map<string, vector<pair<int, int>>> tickettoseats;

    Show(int sid, int mid, int st, int et, int r, int c) : showid(sid), movieid(mid), starttime(st), endtime(et), r(r), c(c)
    {
        empty = r * c;
        for(int i=0; i<r; i++)
        {
            vector<Seat> row;
            for(int j=0; j<c; j++)
            {
                row.push_back(Seat(i, j));
            }
            seats.push_back(row);
        }
    }

    vector<pair<int, int>> book(string ticket, int count)
    {
        vector<pair<int, int>> result;
        if(empty < count)
        {
            return result;
        }
        for(int i=0; i<r; i++)
        {
            for(int j=0; j<c; j++)
            {
                if(seats[i][j].booked == false)
                {
                    seats[i][j].booked = true;
                    result.push_back({i, j});
                    empty--;
                    count--;
                    if(count == 0)
                    {
                        tickettoseats[ticket] = result;
                        return result;
                    }
                }
            }
        }
        return {};
    }

    void cancel(string ticket)
    {
        for(auto& seat : tickettoseats[ticket])
        {
            int i = seat.first, j = seat.second;
            seats[i][j].booked = false;
            empty++;
        }
        tickettoseats.erase(ticket);
    }
};

class Screen {
public:
    int r, c, screenid;
    unordered_map<int, Show> shows;

    Screen(int id, int r, int c) : screenid(id), r(r), c(c) {}

    void addshow(int showid, int movieid, int st, int et)
    {
        shows.emplace(showid, Show(showid, movieid, st, et, r, c));
    }
};

class Cinema {
public:
    int cinemaid;
    unordered_map<int, Screen> screens;

    Cinema(int id) : cinemaid(id) {}

    void addscreen(int screenid, int screenrow, int screencol)
    {
        if(!screens.count(screenid))
        {
            screens.emplace(screenid, Screen(screenid, screenrow, screencol));
        }
    }
    
    set<int> listshows(int movieid)
    {
        set<int> result;
        for(auto& screen : screens)
        {
            Screen& s = screen.second;
            for(auto& show : s.shows)
            {
                Show& sh = show.second;
                if(sh.movieid == movieid)
                {
                    result.insert(sh.showid);
                }
            }
        }
        return result;
    }
};

class City {
public:
    int cityid;
    unordered_map<int, Cinema> cinemas;

    City(int id) : cityid(id) {}

    void addcinema(int cinemaid, int screencount, int screenrow, int screencol)
    {
        if(!cinemas.count(cinemaid))
        {
            cinemas.emplace(cinemaid, Cinema(cinemaid));
        }
        Cinema &cin = cinemas.at(cinemaid);
        for(int i=0; i < screencount; i++)
        {
            cin.addscreen(i, screenrow, screencol);
        }
    }

    set<int> listcinemas(int movieid)
    {
        set<int> result;
        for(auto& cinema : cinemas)
        {
            Cinema& ci = cinema.second;
            bool flag = false;
            for(auto& screen : ci.screens)
            {
                Screen& s = screen.second;
                for(auto& show : s.shows)
                {
                    Show& sh = show.second;
                    if(sh.movieid == movieid)
                    {
                        result.insert(cinema.first);
                        flag = true;
                        break;
                    }
                }
                if(flag)
                {
                    break;
                }
            }
        }
        return result;
    }
};

int main()
{
    string line;
    unordered_map<int, City> cities;
    unordered_map<string, tuple<int, int, int>> tickets;
    while (getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "ADDCINEMA")
        {
            int cityid, cinemaid, screencount, screenrow, screencol;
            ss >> cityid >> cinemaid >> screencount >> screenrow >> screencol;
            if(!cities.count(cityid))
            {
                cities.emplace(cityid, City(cityid));
            }
            cities.at(cityid).addcinema(cinemaid, screencount, screenrow, screencol);
            cout << "Added cinema " << cinemaid << " with " << screencount << " screens in city " << cityid << endl;
        }
        else if(command == "ADDSHOW")
        {
            int cinemaid, screenid, movieid, showid, starttime, endtime;
            ss >> cinemaid >> screenid >> movieid >> showid >> starttime >> endtime;
            for(auto& city : cities)
            {
                City& c = city.second;
                if(c.cinemas.count(cinemaid))
                {
                    c.cinemas.at(cinemaid).screens.at(screenid).addshow(showid, movieid, starttime, endtime);
                    cout << "Added show " << showid << " for movie " << movieid << " in city " << city.first << " cinema " << cinemaid << endl;
                    break;
                }
            }
        }
        else if(command == "BOOK")
        {
            string ticket;
            int showid, count;
            ss >> ticket >> showid >> count;
            bool flag = false;
            for(auto& city : cities)
            {
                City& c = city.second;
                for(auto& cinema : c.cinemas)
                {
                    Cinema& ci = cinema.second;
                    for(auto& screen : ci.screens)
                    {
                        Screen& s = screen.second;
                        for(auto& show : s.shows)
                        {
                            Show& sh = show.second;
                            if(sh.showid == showid)
                            {
                                vector<pair<int, int>> result = sh.book(ticket, count);
                                if(result.empty())
                                {
                                    cout << "FAILURE" << endl;
                                }
                                else
                                {
                                    cout << "SUCCESS" << endl;
                                    tickets.emplace(ticket, make_tuple(city.first, cinema.first, screen.first));
                                    for(int i=0; i<count; i++)
                                    {
                                        cout << "[" << result[i].first << "-" << result[i].second << "] ";
                                    }
                                    cout << endl;
                                }
                                flag = true;
                                break;
                            }
                        }
                        if(flag)
                        {
                            break;
                        }
                    }
                    if(flag)
                    {
                        break;
                    }
                }
                if(flag)
                {
                    break;
                }
            }
        }
        else if(command == "CANCEL")
        {
            string ticket;
            ss >> ticket;
            if(!tickets.count(ticket))
            {
                cout << "FALSE" << endl;
            }
            else
            {
                tuple<int, int, int>& t = tickets[ticket];
                int cityid = get<0>(t), cinemaid = get<1>(t), screenid = get<2>(t);
                City& c = cities.at(cityid);
                Cinema& ci = c.cinemas.at(cinemaid);
                Screen& s = ci.screens.at(screenid);
                bool flag = false;
                for(auto& show : s.shows)
                {
                    Show& sh = show.second;
                    if(sh.tickettoseats.count(ticket))
                    {
                        sh.cancel(ticket);
                        tickets.erase(ticket);
                        flag = true;
                    }
                    if(flag)
                    {
                        break;
                    }
                }
                cout << "TRUE" << endl;
            }
        }
        else if(command == "FREE")
        {
            int showid;
            ss >> showid;
            bool flag = false;
            for(auto& city : cities)
            {
                City& c = city.second;
                for(auto& cinema : c.cinemas)
                {
                    Cinema& ci = cinema.second;
                    for(auto& screen : ci.screens)
                    {
                        Screen& s = screen.second;
                        for(auto& show : s.shows)
                        {
                            Show& sh = show.second;
                            if(sh.showid == showid)
                            {
                                cout << sh.empty << endl;
                                flag = true;
                                break;
                            }
                        }
                        if(flag)
                        {
                            break;
                        }
                    }
                    if(flag)
                    {
                        break;
                    }
                }
                if(flag)
                {
                    break;
                }
            }
        }
        else if(command == "LISTCINEMAS")
        {
            int cityid, movieid;
            ss >> cityid >> movieid;
            City& c = cities.at(cityid);
            set<int> result = c.listcinemas(movieid);
            if(result.empty())
            {
                cout << "[]" << endl;
            }
            else
            {
                for(int c : result)
                {
                    cout << "[" << c << "]";
                }
                cout << endl;
            }
        }
        else if(command == "LISTSHOWS")
        {
            int movieid, cinemaid;
            ss >> movieid >> cinemaid;
            for(auto& city : cities)
            {
                City& c = city.second;
                if(c.cinemas.count(cinemaid))
                {
                    Cinema& ci = c.cinemas.at(cinemaid);
                    set<int> result = ci.listshows(movieid);
                    if(result.empty())
                    {
                        cout << "[]" << endl;
                    }
                    else
                    {
                        for(int c : result)
                        {
                            cout << "[" << c << "]";
                        }
                        cout << endl;
                    }
                }
            }
        }
    }
}

// INPUT:

// ADDCINEMA 1 101 2 3 3
// ADDCINEMA 1 102 1 4 4
// ADDSHOW 101 0 201 1001 900 1200
// ADDSHOW 101 1 202 1002 1300 1600
// ADDSHOW 102 0 201 1003 1000 1300
// BOOK TICKET1 1001 4
// BOOK TICKET2 1002 3
// BOOK TICKET3 1003 5
// FREE 1001
// FREE 1003
// LISTCINEMAS 1 201
// LISTSHOWS 201 101
// CANCEL TICKET1
// FREE 1001
// BOOK TICKET4 1001 6
// LISTSHOWS 202 101
// CANCEL TICKET5

// OUTPUT:

// Added cinema 101 with 2 screens in city 1
// Added cinema 102 with 1 screens in city 1
// Added show 1001 for movie 201 in city 1 cinema 101
// Added show 1002 for movie 202 in city 1 cinema 101
// Added show 1003 for movie 201 in city 1 cinema 102
// SUCCESS
// [0-0] [0-1] [0-2] [1-0]
// SUCCESS
// [0-0] [0-1] [0-2]
// SUCCESS
// [0-0] [0-1] [0-2] [0-3] [1-0]
// 5
// 11
// [101][102]
// [1001]
// TRUE
// 9
// SUCCESS
// [0-0] [0-1] [0-2] [1-0] [1-1] [1-2]
// [1002]
// FALSE