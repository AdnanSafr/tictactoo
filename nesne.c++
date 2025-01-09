#include <iostream>
#include <vector>
using namespace std;

class Board {
public:
    vector<vector<char>> grid;

    Board() {
        grid = vector<vector<char>>(3, vector<char>(3, ' '));
    }

    void display() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << grid[i][j];
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "-----" << endl;
        }
    }

    bool update_cell(int row, int col, char symbol) {
        if (grid[row][col] == ' ') {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    bool is_full() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

class Player {
public:
    string name;
    char symbol;

    Player(string n, char s) : name(n), symbol(s) {}

    void make_move(Board &board) {
        int row, col;
        while (true) {
            cout << name << ", enter row (0-2): ";
            cin >> row;
            cout << name << ", enter column (0-2): ";
            cin >> col;

            if (row < 0 || row > 2 || col < 0 || col > 2) {
                cout << "Invalid input! Row and column must be between 0 and 2." << endl;
                continue;
            }
            if (board.update_cell(row, col, symbol)) {
                break;
            } else {
                cout << "Cell is already taken!" << endl;
            }
        }
    }
};

class Game {
public:
    Board board;
    Player player1;
    Player player2;
    Player *current_player;

    Game() : player1("Player 1", 'X'), player2("Player 2", 'O') {
        current_player = &player1;
    }

    void switch_player() {
        current_player = (current_player == &player1) ? &player2 : &player1;
    }

    bool check_winner() {
        char s = current_player->symbol;
        // Rows, Columns, and Diagonals
        for (int i = 0; i < 3; ++i) {
            if ((board.grid[i][0] == s && board.grid[i][1] == s && board.grid[i][2] == s) || 
                (board.grid[0][i] == s && board.grid[1][i] == s && board.grid[2][i] == s)) {
                return true;
            }
        }
        if ((board.grid[0][0] == s && board.grid[1][1] == s && board.grid[2][2] == s) || 
            (board.grid[0][2] == s && board.grid[1][1] == s && board.grid[2][0] == s)) {
            return true;
        }
        return false;
    }

    void play() {
        cout << "Welcome to Tic Tac Toe!" << endl;
        while (true) {
            board.display();
            current_player->make_move(board);
            if (check_winner()) {
                board.display();
                cout << "Congratulations " << current_player->name << ", you win!" << endl;
                break;
            }
            if (board.is_full()) {
                board.display();
                cout << "It's a draw!" << endl;
                break;
            }
            switch_player();
        }
    }
};

int main() {
    Game game;
    game.play();
 return 0;
}
