#include <iostream>
#include <vector>
#include <string>

using namespace std;

// اندازه صفحه بازی
const int SIZE = 8;

class OthelloGame {
private:
    char board[SIZE][SIZE];
    char currentPlayer;

    // جهت‌های ۸ گانه (بالا، پایین، چپ، راست و قطرها)
    // Directions: {row_change, col_change}
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

public:
    OthelloGame() {
        // ۱. مقداردهی اولیه: همه خانه‌ها خالی (.)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = '.';
            }
        }
        // ۲. چیدن ۴ مهره اولیه در وسط
        board[3][3] = 'W';
        board[3][4] = 'B';
        board[4][3] = 'B';
        board[4][4] = 'W';

        // سیاه همیشه شروع‌کننده است
        currentPlayer = 'B';
    }

    // نمایش صفحه بازی
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

    // بررسی اینکه آیا حرکت در یک جهت خاص باعث تغییر رنگ می‌شود یا خیر
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
                // اگر مهره حریف را دیده باشیم و به مهره خودمان برسیم
                if (sawOpponent) {
                    if (flip) {
                        // برگشتن مسیر و تغییر رنگ مهره‌ها
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
                    return false; // بلافاصله به مهره خودمان رسیدیم (بدون حریف وسط)
                }
            } else {
                return false; // به خانه خالی رسیدیم
            }
            r += dr;
            c += dc;
        }
        return false; // به لبه زمین رسیدیم
    }

    // بررسی اینکه آیا حرکت در خانه مورد نظر معتبر است؟
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

    // انجام حرکت و برگرداندن مهره‌ها
    bool makeMove(int r, int c) {
        if (!isValidMove(r, c)) return false;

        board[r][c] = currentPlayer; // قرار دادن مهره جدید

        // بررسی تمام جهات برای تغییر رنگ مهره‌های حریف
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

        // شرط پایان بازی: پر شدن صفحه (ساده‌ترین حالت)
        // در نسخه کامل‌تر باید بررسی شود که هر دو بازیکن حرکت نداشته باشند (که در بالا چک شد)
    }

    game.getScore();
    return 0;
}