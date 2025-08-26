#include<bits/stdc++.h>
using namespace std;

class Food {
    public:

    string id;
    double rating;
    int numrating;

    Food() : rating(0.0), numrating(0.0), id("") {}

    Food(string id) : rating(0.0), numrating(0), id(id) {}

    void rate(int r)
    {
        rating = ((rating * numrating) + r) / (numrating + 1);
        numrating++;
    }
};

class Order{
    public:

    string id;
    vector<string> items;

    Order() : id("") {}

    Order(string id) : id(id) {}

    void additem(string& id)
    {
        items.push_back(id);
    }
};

class Restaurant {
    public:

    double rating;
    int numrating;
    unordered_map<string, Food> menu;
    unordered_map<string, Order> orders;

    Restaurant() : rating(0.0), numrating(0) {}

    void addfood(string id)
    {
        if(!menu.count(id))
        {
            menu[id] = Food(id);
        }
    }

    void order(string& orderid, string& foodid, string& restaurantid)
    {
        addfood(foodid);
        orders[orderid] = Order(orderid);
        orders[orderid].additem(foodid);
        cout << "Order " << orderid << " placed at restaurant " << restaurantid << " for food item " << foodid << endl;
    }

    void rate(string& orderid, int r)
    {
        cout << "Old rating of food: " << menu[orders[orderid].items[0]].rating << " and restaurant " << rating << endl;
        menu[orders[orderid].items[0]].rate(r);
        rating = ((rating * numrating + r)) / (numrating + 1);
        numrating++;
        cout << "New rating of food: " << menu[orders[orderid].items[0]].rating << " and restaurant " << rating << endl;
    }
};

int main()
{
    string line;
    unordered_map<string, Restaurant> restaurants;
    unordered_map<string, string> ordertorestaurant;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "ORDER")
        {
            string orderid, restaurantid, foodid;
            ss >> orderid >> restaurantid >> foodid;
            if(!restaurants.count(restaurantid))
            {
                restaurants[restaurantid] = Restaurant();
            }
            restaurants[restaurantid].order(orderid, foodid, restaurantid);
            ordertorestaurant[orderid] = restaurantid;
        }
        else if(command == "RATE")
        {
            string orderid;
            int rating;
            ss >> orderid >> rating;
            restaurants[ordertorestaurant[orderid]].rate(orderid, rating);
        }
        else if(command == "GETTOPRESTAURANT")
        {
            string foodid;
            ss >> foodid;
            string best;
            double bestrating = -1.0;
            int mostrating = 0;
            for(auto& restaurant : restaurants)
            {
                Restaurant& r = restaurant.second;
                if(r.menu[foodid].rating > bestrating)
                {
                    bestrating = r.menu[foodid].rating;
                    best = restaurant.first;
                    mostrating = r.menu[foodid].numrating;
                }
                else if(r.menu[foodid].rating == bestrating && mostrating < r.menu[foodid].numrating)
                {
                    mostrating = r.menu[foodid].numrating;
                    best = restaurant.first;
                }
            }
            cout << "Best rated restaurant for food " << foodid << " is: " << best << "(" << bestrating << ")" << endl;
        }
        else if(command == "GETTOP")
        {
            string best;
            double bestrating = -1.0;
            int mostrating = 0;
            for(auto& restaurant : restaurants)
            {
                Restaurant& r = restaurant.second;
                if(r.rating > bestrating)
                {
                    bestrating = r.rating;
                    best = restaurant.first;
                    mostrating = r.numrating;
                }
                else if(r.rating == bestrating && mostrating < r.numrating)
                {
                    mostrating = r.numrating;
                    best = restaurant.first;
                }
            }
            cout << "Best rated restaurant is: " << best << "(" << bestrating << ")" << endl;
        }
    }
}

// INPUT:

// ORDER o1 r1 pizza
// ORDER o2 r1 burger
// ORDER o3 r2 pizza
// RATE o1 5
// RATE o2 3
// RATE o3 4
// GETTOPRESTAURANT pizza
// GETTOP

// OUTPUT:

// Order o1 placed at restaurant r1 for food item pizza
// Order o2 placed at restaurant r1 for food item burger
// Order o3 placed at restaurant r2 for food item pizza
// Old rating of food: 0 and restaurant 0
// New rating of food: 5 and restaurant 5
// Old rating of food: 0 and restaurant 5
// New rating of food: 3 and restaurant 4
// Old rating of food: 0 and restaurant 0
// New rating of food: 4 and restaurant 4
// Best rated restaurant for food pizza is: r1(5)
// Best rated restaurant is: r1(4)