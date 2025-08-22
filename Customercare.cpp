#include<bits/stdc++.h>
using namespace std;

enum Status {
    OPEN, ASSIGNED, RESOLVED
};

class Issue {
    public:

    string issueid, orderid, type, description;
    Status status;
    string agent;
    string resolution;

    Issue(string id = "", string oid = "", string type = "", string description = "") : issueid(id), orderid(oid), type(type), description(description), status(OPEN), agent(""), resolution("") {}
};

class Agent {
    public:

    string id;
    unordered_set<string> expertise;
    unordered_set<string> open;
    vector<string> resolved;
    unordered_map<string, int> resolvedtype;
    unordered_map<string, int> opentype;

    Agent(string id = "", vector<string> exp = {}) : id(id)
    {
        for(string e : exp)
        {
            expertise.insert(e);
        }
    }
};

class CustomerSystem {
    public:

    unordered_map<string, Issue> issues;
    unordered_set<string> issuetypes;
    unordered_map<string, Agent> agents;

    void init(vector<string>& types)
    {
        issuetypes.clear();
        for(string& type : types)
        {
            issuetypes.insert(type);
        }
        issues.clear();
        agents.clear();
        cout << "Initialized " << types.size() << " issue types" << endl;
    }

    void createissue(string issueid, string orderid, string type, string desc)
    {
        if(!issuetypes.count(type))
        {
            cout << "Invalid issue type" << endl;
            return;
        }
        if(issues.count(issueid))
        {
            cout << "Issue already exists" << endl;
            return;
        }
        Issue issue(issueid, orderid, type, desc);
        issues[issueid] = issue;
        cout << "Issue created with issueid: " << issueid << " and orderid: " << orderid << endl;
        return;
    }

    void createagent(string id, vector<string>& exp)
    {
        if(agents.count(id))
        {
            cout << "Agent already exists" << endl;
        }
        agents[id] = Agent(id, exp);
        cout << "SUCCESS" << endl;
    }

    void assign(string id, int strategy)
    {
        if(!issues.count(id))
        {
            cout << "Issue not found" << endl;
            return;
        }
        if(issues[id].status != OPEN)
        {
            cout << "Issue already assigned or resolved" << endl;
            return;
        }
        string best;
        if(strategy == 0)
        {
            int lowest = INT_MAX;
            for(auto& agent : agents)
            {
                Agent& a  = agent.second;
                if(a.open.size() < lowest && a.expertise.count(issues[id].type))
                {
                    lowest = a.open.size();
                    best = agent.first;
                }
            }
        }
        else if(strategy == 1)
        {
            int highest = INT_MIN;
            for(auto& agent : agents)
            {
                Agent& a = agent.second;
                if(a.resolvedtype[issues[id].type] > highest && a.expertise.count(issues[id].type))
                {
                    highest = a.resolvedtype[issues[id].type];
                    best = agent.first;
                }
            }
        }
        else if(strategy == 2)
        {
            int lowest = INT_MAX;
            for(auto& agent : agents)
            {
                Agent& a = agent.second;
                if(a.opentype[issues[id].type] < lowest && a.expertise.count(issues[id].type))
                {
                    lowest = a.opentype[issues[id].type];
                    best = agent.first;
                }
            }
        }
        agents[best].open.insert(id);
        agents[best].opentype[issues[id].type]++;
        issues[id].agent = best;
        issues[id].status = ASSIGNED;
        cout << "Issue " << id << " assigned to agent " << best << endl;
    }

    void resolve(string id, string resolution)
    {
        if(issues[id].status == OPEN)
        {
            cout << "Agent not assigned yet" << endl;
            return;
        }
        else if(issues[id].status == RESOLVED)
        {
            cout << "Issue resolved already" << endl;
            return;
        }
        issues[id].status = RESOLVED;
        issues[id].resolution = resolution;
        Agent &ag = agents[issues[id].agent];
        ag.open.erase(id);
        ag.resolved.emplace_back(id);
        ag.resolvedtype[issues[id].type]++;
        ag.opentype[issues[id].type]--;
        cout << "Issue " << id << " resolved by agent " << issues[id].agent << endl;
    }

    vector<string> gethistory(string id)
    {
        return agents[id].resolved;
    }
};

int main()
{
    string line;
    CustomerSystem system;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "INIT")
        {
            int n;
            ss >> n;
            vector<string> types(n);
            for(int i=0; i<n; i++)
            {
                ss >> types[i];
            }
            system.init(types);
        }
        else if(command == "CREATEISSUE")
        {
            string issueid, orderid, type, desc;
            ss >> issueid >> orderid >> type >> desc;
            system.createissue(issueid, orderid, type, desc);
        }
        else if(command == "CREATEAGENT")
        {
            string id;
            int n;
            ss >> id >> n;
            vector<string> exp(n);
            for(int i=0; i<n; i++)
            {
                ss >> exp[i];
            }
            system.createagent(id, exp);
        }
        else if(command == "ASSIGN")
        {
            string id;
            int strategy;
            ss >> id >> strategy;
            system.assign(id, strategy);
        }
        else if(command == "RESOLVE")
        {
            string id, resolution;
            ss >> id >> resolution;
            system.resolve(id, resolution);
        }
        else if(command == "GETHISTORY")
        {
            string id;
            ss >> id;
            vector<string> result = system.gethistory(id);
            cout << "Agent " << id << " has resolved the following issues:" << endl;
            for(string r : result)
            {
                cout << r << " ";
            }
            cout << endl;
        }
    }
}

// INPUT:

// INIT 5 payment delivery refund technical account
// CREATEAGENT A1 2 payment refund
// CREATEAGENT A2 3 delivery payment account
// CREATEAGENT A3 2 technical delivery
// CREATEAGENT A4 1 account
// CREATEAGENT A5 3 payment delivery technical
// CREATEISSUE I1 O1 payment "Payment failed at checkout"
// CREATEISSUE I2 O2 delivery "Package not delivered on time"
// CREATEISSUE I3 O3 refund "Refund not processed for cancelled order"
// CREATEISSUE I4 O4 technical "App crashes on login"
// CREATEISSUE I5 O5 account "Unable to reset password"
// CREATEISSUE I6 O6 payment "Double charge detected"
// CREATEISSUE I7 O7 delivery "Damaged item received"
// CREATEISSUE I8 O8 technical "Website not loading"
// CREATEISSUE I9 O9 refund "Partial refund not issued"
// CREATEISSUE I10 O10 account "Email not verified"
// ASSIGN I1 1
// ASSIGN I2 1
// ASSIGN I3 1
// ASSIGN I4 1
// ASSIGN I5 1
// ASSIGN I6 1
// ASSIGN I7 1
// ASSIGN I8 1
// ASSIGN I9 1
// ASSIGN I10 1
// RESOLVE I1 fixed
// RESOLVE I2 compensated
// RESOLVE I3 refunded
// RESOLVE I4 patched
// RESOLVE I5 reset
// RESOLVE I6 refunded
// RESOLVE I7 replaced
// RESOLVE I8 restored
// RESOLVE I9 refunded
// RESOLVE I10 updated
// GETHISTORY A1
// GETHISTORY A2
// GETHISTORY A3
// GETHISTORY A4
// GETHISTORY A5

// OUTPUT:

// Initialized 5 issue types
// SUCCESS
// SUCCESS
// SUCCESS
// SUCCESS
// SUCCESS
// Issue created with issueid: I1 and orderid: O1
// Issue created with issueid: I2 and orderid: O2
// Issue created with issueid: I3 and orderid: O3
// Issue created with issueid: I4 and orderid: O4
// Issue created with issueid: I5 and orderid: O5
// Issue created with issueid: I6 and orderid: O6
// Issue created with issueid: I7 and orderid: O7
// Issue created with issueid: I8 and orderid: O8
// Issue created with issueid: I9 and orderid: O9
// Issue created with issueid: I10 and orderid: O10
// Issue I1 assigned to agent A5
// Issue I2 assigned to agent A5
// Issue I3 assigned to agent A1
// Issue I4 assigned to agent A5
// Issue I5 assigned to agent A4
// Issue I6 assigned to agent A5
// Issue I7 assigned to agent A5
// Issue I8 assigned to agent A5
// Issue I9 assigned to agent A1
// Issue I10 assigned to agent A4
// Issue I1 resolved by agent A5
// Issue I2 resolved by agent A5
// Issue I3 resolved by agent A1
// Issue I4 resolved by agent A5
// Issue I5 resolved by agent A4
// Issue I6 resolved by agent A5
// Issue I7 resolved by agent A5
// Issue I8 resolved by agent A5
// Issue I9 resolved by agent A1
// Issue I10 resolved by agent A4
// Agent A1 has resolved the following issues:
// I3 I9
// Agent A2 has resolved the following issues:

// Agent A3 has resolved the following issues:

// Agent A4 has resolved the following issues:
// I5 I10
// Agent A5 has resolved the following issues:
// I1 I2 I4 I6 I7 I8