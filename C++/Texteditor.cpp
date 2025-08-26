#include<bits/stdc++.h>
using namespace std;

struct Character {
    public:

    char c;
    int size;
    bool bold;
    bool italic;
    string font;

    Character(char c = '\0', int size = 0, bool bold = false, bool italic = false, string font = "") : c(c), size(size), bold(bold), italic(italic), font(font) {}
};

class Editor {
    public:

    int r, c;
    vector<vector<Character>> rows;

    Editor()
    {
        rows.clear();
        r = 0;
        c = 0;
    }

    void ensurerow(int row)
    {
        if(row >= r)
        {
            rows.resize(row+1);
            r = row+1;
        }
    }

    void insert(int row, int col, char ch, string font, int size, bool b, bool i)
    {
        ensurerow(row);
        auto& line = rows[row];
        Character newchar(ch, size, b, i, font);
        if(col < 0)
        {
            col = 0;
        }
        if(col >= (int)line.size())
        {
            line.push_back(newchar);
        }
        else
        {
            line.insert(line.begin() + col, newchar);
        }
        cout << "Appended character " << ch << " at row " << row << " column " << col << endl;
    }

    void getstyle(int row, int col)
    {
        if(row >= r || col >= (int)rows[row].size())
        {
            cout << "No character found at row " << row << " column " << col << endl;
            return;
        }

        Character& character = rows[row][col];
        if(character.c != '\0')
        {
            cout << character.c << "-" << character.font << "-" << character.size;
            if(character.bold)
            {
                cout << "-b";
            }
            if(character.italic)
            {
                cout << "-i";
            }
        }
        else
        {
            cout << "No character found at row " << row << " column " << col;
        }
        cout << endl;
    }

    void readline(int row)
    {
        string result = "";
        if(row >= r)
        {
            cout << result << endl;
            return;
        }
        for(auto& ch : rows[row])
        {
            if(ch.c != '\0')
            {
                result += ch.c;
            }
        }
        cout << result << endl;
    }

    void deletechar(int row, int col)
    {
        if(row < r && col < (int)rows[row].size())
        {
            rows[row].erase(rows[row].begin() + col);
        }
    }
};

int main()
{
    string line;
    Editor editor;
    while(getline(cin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "ADD")
        {
            int row, column, size;
            char c;
            string font;
            bool bold, italic;
            ss >> row >> column >> c >> font >> size >> bold >> italic;
            editor.insert(row, column, c, font, size, bold, italic);
        }
        else if(command == "GETSTYLE")
        {
            int row, column;
            ss >> row >> column;
            editor.getstyle(row, column);
        }
        else if(command == "READLINE")
        {
            int row;
            ss >> row;
            editor.readline(row);
        }
        else if(command == "DELETE")
        {
            int row, column;
            ss >> row >> column;
            editor.deletechar(row, column);
        }
    }
}

// INPUT:

// ADD 0 0 g Cambria 17 1 1
// ADD 1 0 y Century 14 1 1
// ADD 1 1 h Courier 22 0 0
// ADD 1 2 y Georgia 14 0 0
// GETSTYLE 0 0
// READLINE 0
// ADD 0 0 q Arial 21 0 1
// READLINE 0
// READLINE 1
// DELETE 1 1
// READLINE 1

// OUTPUT:

// Appended character g at row 0 column 0
// Appended character y at row 1 column 0
// Appended character h at row 1 column 1
// Appended character y at row 1 column 2
// g-Cambria-17-b-i
// g
// Appended character q at row 0 column 0
// qg
// yhy
// yy