#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int SIZE = 8;

class OthelloGame {
private:
    char board[SIZE][SIZE];
    char currentPlayer;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

public:
    OthelloGame() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = '.';
            }
        }
        board[3][3] = 'W';
        board[3][4] = 'B';
        board[4][3] = 'B';
        board[4][4] = 'W';
        currentPlayer = 'B';
    }
    void printBoard() {
        cout << "  0 1 2 3 4 5 6 7" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool checkDirection(int r, int c, int dr, int dc, bool flip) {
        char opponent = (currentPlayer == 'B') ? 'W' : 'B';
        int rOriginal = r, cOriginal = c;
        bool sawOpponent = false;

        r += dr;
        c += dc;

        while (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
            if (board[r][c] == opponent) {
                sawOpponent = true;
            } else if (board[r][c] == currentPlayer) {
                if (sawOpponent) {
                    if (flip) {
                        int rr = rOriginal + dr;
                        int cc = cOriginal + dc;
                        while (rr != r || cc != c) {
                            board[rr][cc] = currentPlayer;
                            rr += dr;
                            cc += dc;
                        }
                    }
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
            r += dr;
            c += dc;
        }
        return false;
    }

    bool isValidMove(int r, int c) {
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] != '.')
            return false;

        for (int i = 0; i < 8; i++) {
            if (checkDirection(r, c, directions[i][0], directions[i][1], false)) {
                return true;
            }
        }
        return false;
    }

    bool makeMove(int r, int c) {
        if (!isValidMove(r, c)) return false;
        board[r][c] = currentPlayer;
        for (int i = 0; i < 8; i++) {
            checkDirection(r, c, directions[i][0], directions[i][1], true);
        }
        switchTurn();
        return true;
    }

    void switchTurn() {
        currentPlayer = (currentPlayer == 'B') ? 'W' : 'B';
    }

    bool hasValidMoves() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (isValidMove(i, j)) return true;
            }
        }
        return false;
    }

    char getCurrentPlayer() { return currentPlayer; }

    void getScore() {
        int blackScore = 0, whiteScore = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 'B') blackScore++;
                else if (board[i][j] == 'W') whiteScore++;
            }
        }
        cout << "Black (B): " << blackScore << " | White (W): " << whiteScore << endl;
        if (blackScore > whiteScore) cout << "Black Wins!" << endl;
        else if (whiteScore > blackScore) cout << "White Wins!" << endl;
        else cout << "Draw!" << endl;
    }
};

int main() {
    OthelloGame game;
    int row, col;

    while (true) {
        game.printBoard();

        if (!game.hasValidMoves()) {
            cout << "Player " << game.getCurrentPlayer() << " has no valid moves. Passing turn..." << endl;
            game.switchTurn();
            if (!game.hasValidMoves()) {
                cout << "No moves left for either player. Game Over!" << endl;
                break;
            }
            continue;
        }

        cout << "Player " << game.getCurrentPlayer() << "'s turn (Enter row col): ";
        cin >> row >> col;

        if (!game.makeMove(row, col)) {
            cout << "Invalid move! Try again." << endl;
        }
    }

    game.getScore();
    return 0;
}