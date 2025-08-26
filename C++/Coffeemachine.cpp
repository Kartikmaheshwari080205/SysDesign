#include<bits/stdc++.h>
using namespace std;

class Item {
    public:

    string id;
    unordered_map<string, int> recipe;

    Item(string id = "", vector<pair<string, int>> r = {}) : id(id)
    {
        for(auto& ingredient : r)
        {
            recipe[ingredient.first] = ingredient.second;
        }
    }
};

class Ingredient {
    public:

    string id;
    int quantity;

    Ingredient(string id = "", int quantity = 0) : id(id), quantity(quantity) {}
};

class CoffeeMachine {
    public:

    unordered_map<string, Ingredient> ingredients;
    unordered_map<string, Item> items;

    void addingredient(string id, int quantity)
    {
        if(ingredients.count(id))
        {
            ingredients[id].quantity += quantity;
        }
        else
        {
            ingredients[id] = Ingredient(id, quantity);
        }
        cout << "ADDED " << quantity << " units of " << id << endl;
        return;
    }

    void additem(string id, vector<pair<string, int>> recipe)
    {
        if(items.count(id))
        {
            cout << "ITEM " << id << " already exist" << endl;
            return;
        }
        items[id] = Item(id, recipe);
        cout << "Item " << id << " added" << endl;
        return;
    }

    void makeitem(string id)
    {
        if(!items.count(id))
        {
            cout << "Item " << id << " does not exist" << endl;
            return;
        }
        Item& item = items[id];
        bool flag = true;
        for(auto& ingredient : item.recipe)
        {
            if(ingredient.second > ingredients[ingredient.first].quantity)
            {
                flag = false;
                break;
            }
        }
        if(!flag)
        {
            cout << "Not enough ingredients for item " << id << endl;
            return;
        }
        for(auto& ingredient : ingredients)
        {
            ingredient.second.quantity -= item.recipe[ingredient.first];
        }
        cout << "Item " << id << " prepared" << endl;
        return;
    }

    void getstate()
    {
        cout << "Ingredients:" << endl;
        for(auto& ingredient : ingredients)
        {
            cout << ingredient.first << ": " << ingredient.second.quantity << endl;
        }
        cout << "Items: ";
        for(auto& item : items)
        {
            cout << item.first << " ";
        }
        cout << endl;
        return;
    }
};

int main()
{
    string line;
    CoffeeMachine machine;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        {
            if(command == "ADDINGREDIENT")
            {
                string id;
                int quantity;
                ss >> id >> quantity;
                machine.addingredient(id, quantity);
            }
            else if(command == "ADDITEM")
            {
                string id;
                int n;
                ss >> id >> n;
                vector<pair<string, int>> recipe;
                for(int i=0; i<n; i++)
                {
                    string id;
                    int quantity;
                    ss >> id >> quantity;
                    recipe.push_back({id, quantity});
                }
                machine.additem(id, recipe);
            }
            else if(command == "MAKEITEM")
            {
                string id;
                ss >> id;
                machine.makeitem(id);
            }
            else if(command == "GETSTATE")
            {
                machine.getstate();
            }
        }
    }
}

// INPUT:

// ADDINGREDIENT Milk 5
// ADDINGREDIENT CoffeeBeans 3
// ADDINGREDIENT Sugar 2
// ADDITEM Cappuccino 3 Milk 2 CoffeeBeans 1 Sugar 1
// ADDITEM Cappuccino 3 Milk 2 CoffeeBeans 1 Sugar 1
// ADDITEM Espresso 2 CoffeeBeans 2 Sugar 1
// MAKEITEM Cappuccino
// MAKEITEM Latte
// MAKEITEM Espresso
// MAKEITEM Espresso
// GETSTATE
// ADDINGREDIENT CoffeeBeans 5
// MAKEITEM Espresso
// GETSTATE

// OUTPUT:

// ADDED 5 units of Milk
// ADDED 3 units of CoffeeBeans
// ADDED 2 units of Sugar
// Item Cappuccino added
// ITEM Cappuccino already exist
// Item Espresso added
// Item Cappuccino prepared
// Item Latte does not exist
// Item Espresso prepared
// Not enough ingredients for item Espresso
// Ingredients:
// Sugar: 0
// CoffeeBeans: 0
// Milk: 3
// Items: Espresso Cappuccino
// ADDED 5 units of CoffeeBeans
// Not enough ingredients for item Espresso
// Ingredients:
// Sugar: 0
// CoffeeBeans: 5
// Milk: 3
// Items: Espresso Cappuccino