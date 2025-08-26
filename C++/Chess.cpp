#include<bits/stdc++.h>
using namespace std;

class Piece;
class Queen;
class Rook;
class Bishop;
class Knight;

class Cell {
    public:
    string color;
    Piece* piece;

    Cell() : piece(nullptr) {}
};

class Piece {
    public:
    string color, name;
    bool hasmoved = false;

    Piece(string c, string n) : color(c), name(n) {}

    virtual set<pair<int, int>> getmoves(int x, int y, const vector<vector<Cell>>& board) = 0;

    virtual ~Piece() {}

    string code()
    {
        return (color == "white" ? "W" : "B") + name;
    }

    protected:
    set<pair<int, int>> slidemoves(int x, int y, const vector<vector<Cell>>& board, const vector<pair<int, int>>& directions) const
    {
        set<pair<int, int>> moves;
        for(auto& dir : directions)
        {
            int nx = x + dir.first, ny = y + dir.second;
            while(nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
            {
                if(board[nx][ny].piece == nullptr)
                {
                    moves.insert({nx, ny});
                }
                else
                {
                    if(board[nx][ny].piece->color != color)
                    {
                        moves.insert({nx, ny});
                    }
                    break;
                }
                nx += dir.first;
                ny += dir.second;
            }
        }
        return moves;
    }
};

class Rook : public Piece {
    public:
    vector<pair<int,int>> directions = {{1, 0},{-1, 0},{0, 1},{0, -1}};
    Rook(string s) : Piece(s, "R") {}

    set<pair<int, int>> getmoves(int x, int y, const vector<vector<Cell>>& board) override
    {
        return slidemoves(x, y, board, directions);
    }
};

class Knight : public Piece {
    public:
    vector<int> dx = {2, 2, 1, 1, -1, -1, -2, -2};
    vector<int> dy = {1, -1, 2, -2, 2, -2, 1, -1};
    Knight(string s) : Piece(s, "H") {}

    set<pair<int, int>> getmoves(int x, int y, const vector<vector<Cell>>& board) override
    {
        set<pair<int, int>> moves;
        for(int i=0; i<8; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
            {
                if(board[nx][ny].piece == nullptr || board[nx][ny].piece->color != color)
                {
                    moves.insert({nx, ny});
                }
            }
        }
        return moves;
    }
};

class Bishop : public Piece {
    public:
    vector<pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    Bishop(string s) : Piece(s, "B") {}

    set<pair<int, int>> getmoves(int x, int y, const vector<vector<Cell>>& board) override
    {
        return slidemoves(x, y, board, directions);
    }
};

class Queen : public Piece {
    public:
    vector<pair<int, int>> directions = {{1, 0},{-1, 0},{0, 1},{0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    Queen(string s) : Piece(s, "Q") {}

    set<pair<int, int>> getmoves(int x, int y, const vector<vector<Cell>>& board) override
    {
        return slidemoves(x, y, board, directions);
    }
};

class King : public Piece {
    public:
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    King(string s) : Piece(s, "K") {}

    set<pair<int, int>> getmoves(int x, int y, const vector<vector<Cell>>& board) override
    {
        set<pair<int, int>> moves;
        for(auto& direction : directions)
        {
            int nx = x + direction.first, ny = y + direction.second;
            if(nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
            {
                if(board[nx][ny].piece == nullptr || board[nx][ny].piece->color != color)
                {
                    moves.insert({nx, ny});
                }
            }
        }
        if(!hasmoved)
        {
            if(y+1 < 8 && y+2 < 8 && board[x][y+1].piece == nullptr && board[x][y+2].piece == nullptr)
            {
                if(board[x][7].piece != nullptr && board[x][7].piece->name == "R")
                {
                    Rook* rook = dynamic_cast<Rook*>(board[x][7].piece);
                    if(rook && !rook->hasmoved)
                    {
                        moves.insert({x, y+2});
                    }
                }
            }
            if(y-1 >= 0 && y-2 >= 0 && y-3 >= 0 && board[x][y-1].piece == nullptr && board[x][y-2].piece == nullptr && board[x][y-3].piece == nullptr)
            {
                if(board[x][0].piece != nullptr && board[x][0].piece->name == "R")
                {
                    Rook* rook = dynamic_cast<Rook*>(board[x][0].piece);
                    if(rook && !rook->hasmoved)
                    {
                        moves.insert({x, y-2});
                    }
                }
            }
        }
        return moves;
    }
};

class Pawn : public Piece {
    public:
    Pawn(string s) : Piece(s, "P") {}

    set<pair<int, int>> getmoves(int x, int y, const vector<vector<Cell>>& board) override
    {
        set<pair<int, int>> moves;
        int direction = (color == "white") ? 1 : -1;
        int nx = x + direction;
        if(nx >= 0 && nx < 8 && board[nx][y].piece == nullptr)
        {
            moves.insert({nx, y});
            if((color == "white" && x == 1) || (color == "black" && x == 6))
            {
                int nx2 = x + 2 * direction;
                if(nx2 >= 0 && nx2 < 8 && board[nx2][y].piece == nullptr)
                {
                    moves.insert({nx2, y});
                }
            }
        }
        for(int dy : {-1, 1})
        {
            int ny = y + dy;
            if(nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
            {
                if(board[nx][ny].piece != nullptr && board[nx][ny].piece->color != color)
                {
                    moves.insert({nx, ny});
                }
            }
        }
        return moves;
    }

    static void checkPromotion(int x, int y, vector<vector<Cell>>& board, ifstream& infile)
    {
        Piece* pawn = board[x][y].piece;
        if(pawn == nullptr || pawn->name != "P")
        {
            return;
        }
        if((pawn->color == "white" && x == 7) || (pawn->color == "black" && x == 0))
        {
            cout << "Pawn promoted! Reading choice from file...";
            char choice;
            if(cin >> choice)
            {
                cout << " Chosen: " << choice << endl;
            }
            else
            {
                choice = 'Q';
                cout << " No choice in file, defaulting to Queen" << endl;
            }
            string c = pawn->color;
            delete board[x][y].piece;
            if(choice == 'Q')
            {
                board[x][y].piece = new Queen(c);
            }
            else if(choice == 'R')
            {
                board[x][y].piece = new Rook(c);
            }
            else if(choice == 'B')
            {
                board[x][y].piece = new Bishop(c);
            }
            else
            {
                board[x][y].piece = new Knight(c);
            }
        }
    }
};

class Board {
    public:
    bool gameover, whiteturn;
    vector<vector<Cell>> board;
    
    Board() : gameover(false), whiteturn(true)
    {
        for(int i=0; i<8; i++)
        {
            vector<Cell> row;
            for(int j=0; j<8; j++)
            {
                Cell cell;
                if(i % 2 == 0)
                {
                    if(j % 2 == 0)
                    {
                        cell.color = "white";
                    }
                    else
                    {
                        cell.color = "black";
                    }
                }
                else
                {
                    if(j % 2 == 0)
                    {
                        cell.color = "black";
                    }
                    else
                    {
                        cell.color = "white";
                    }
                }
                row.push_back(cell);
            }
            board.push_back(row);
        }
        initializepieces();
    }

    void initializepieces()
    {
        board[0][0].piece = new Rook("white");
        board[0][1].piece = new Knight("white");
        board[0][2].piece = new Bishop("white");
        board[0][3].piece = new Queen("white");
        board[0][4].piece = new King("white");
        board[0][5].piece = new Bishop("white");
        board[0][6].piece = new Knight("white");
        board[0][7].piece = new Rook("white");
        for(int i=0; i<8; i++)
        {
            board[1][i].piece = new Pawn("white");
            board[6][i].piece = new Pawn("black");
        }
        board[7][0].piece = new Rook("black");
        board[7][1].piece = new Knight("black");
        board[7][2].piece = new Bishop("black");
        board[7][3].piece = new Queen("black");
        board[7][4].piece = new King("black");
        board[7][5].piece = new Bishop("black");
        board[7][6].piece = new Knight("black");
        board[7][7].piece = new Rook("black");
    }

    void printboard()
    {
        cout << "  0 1 2 3 4 5 6 7" << endl;
        for(int i=0; i<8; i++)
        {
            cout << i << " ";
            for(int j=0; j<8; j++)
            {
                if(board[i][j].piece)
                {
                    cout << board[i][j].piece->code() << " ";
                }
                else
                {
                    cout << " . ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    bool isSquareAttacked(int x, int y, string attackerColor) const
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                Piece* p = board[i][j].piece;
                if(p && p->color == attackerColor)
                {
                    auto m = p->getmoves(i, j, board);
                    if(m.count({x, y}))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void makemove(int sr, int sc, int er, int ec, ifstream& infile)
    {
        cout << "DEBUG: Attempting move from (" << sr << "," << sc << ") to (" << er << "," << ec << ")" << endl;
        
        string turn = whiteturn ? "white" : "black";
        cout << "DEBUG: Current turn: " << turn << endl;
        if(board[sr][sc].piece == nullptr)
        {
            cout << "DEBUG: No piece at source position (" << sr << "," << sc << ")" << endl;
            cout << "Invalid Move" << endl;
            return;
        }
        cout << "DEBUG: Piece at source: " << board[sr][sc].piece->code() << " (color: " << board[sr][sc].piece->color << ")" << endl;
        if(board[sr][sc].piece->color != turn)
        {
            cout << "DEBUG: Wrong turn! Piece color is " << board[sr][sc].piece->color << " but turn is " << turn << endl;
            cout << "Invalid Move" << endl;
            return;
        }
        set<pair<int, int>> moves = board[sr][sc].piece->getmoves(sr, sc, board);
        cout << "DEBUG: Valid moves for this piece: ";
        for(auto& move : moves)
        {
            cout << "(" << move.first << "," << move.second << ") ";
        }
        cout << endl;
        if(moves.count({er, ec}) == 0)
        {
            cout << "DEBUG: Target position (" << er << "," << ec << ") is not in valid moves list" << endl;
            cout << "Invalid Move" << endl;
            return;
        }
        cout << "DEBUG: Move is valid, executing..." << endl;
        Piece* movingpiece = board[sr][sc].piece;
        if(board[er][ec].piece && board[er][ec].piece->color != turn)
        {
            cout << "DEBUG: Capturing enemy piece: " << board[er][ec].piece->code() << endl;
            delete board[er][ec].piece;
        }
        if(movingpiece->name == "K" && abs(ec - sc) == 2)
        {
            cout << "DEBUG: Castling detected" << endl;
            if(ec == 6)
            {
                cout << "DEBUG: Kingside castling" << endl;
                board[sr][5].piece = board[sr][7].piece;
                board[sr][7].piece = nullptr;
                board[sr][5].piece->hasmoved = true;
            }
            else if(ec == 2)
            {
                cout << "DEBUG: Queenside castling" << endl;
                board[sr][3].piece = board[sr][0].piece;
                board[sr][0].piece = nullptr;
                board[sr][3].piece->hasmoved = true;
            }
        }
        board[er][ec].piece = movingpiece;
        board[sr][sc].piece = nullptr;
        movingpiece->hasmoved = true;
        Pawn::checkPromotion(er, ec, board, infile);
        whiteturn = !whiteturn;
        cout << "Move successful!" << endl;
        printboard();
    }

    ~Board()
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                delete board[i][j].piece;
                board[i][j].piece = nullptr;
            }
        }
    }
};

int main()
{
    Board b = Board();
    cout << "Current turn: " << (b.whiteturn ? "White" : "Black") << endl << endl;
    b.printboard();
    ifstream infile("moves.txt");
    if(!infile.is_open())
    {
        cout << "Error: Could not open moves.txt file!" << endl;
        return 1;
    }
    string command;
    while(!b.gameover && infile >> command)
    {
        cout << "DEBUG: Read command: " << command << endl;
        if(command == "MOVE")
        {
            int sr, sc, er, ec;
            if(infile >> sr >> sc >> er >> ec)
            {
                cout << "DEBUG: Read move coordinates: " << sr << " " << sc << " " << er << " " << ec << endl;
                b.makemove(sr, sc, er, ec, infile);
                cout << "Current turn: " << (b.whiteturn ? "White" : "Black") << endl << endl;
            }
            else
            {
                cout << "ERROR: Could not read move coordinates from file" << endl;
                break;
            }
        }
        else if(command == "EXIT")
        {
            cout << "Game Over" << endl;
            break;
        }
        else
        {
            cout << "Unknown command in file: " << command << endl;
        }
    }
    infile.close();
}