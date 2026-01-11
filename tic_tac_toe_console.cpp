#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

class TicTacToe {
private:
    vector<int> board; // 0 = empty, 1 = X (player), 2 = O (computer)

    int checkThree(int a, int b, int c) const {
        if (board[a] == board[b] && board[b] == board[c] && board[a] != 0) {
            return board[a];
        }
        return 0;
    }

    int findWinningMove(int player) {
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = player;
                int w = checkWinner();
                board[i] = 0;
                if (w == player) return i;
            }
        }
        return -1;
    }

public:
    TicTacToe() : board(9, 0) {}

    void resetBoard() {
        fill(board.begin(), board.end(), 0);
    }

    int getCell(int idx) const {
        if (idx < 0 || idx > 8) return -1;
        return board[idx];
    }

    int checkWinner() const {
        // Check rows
        int w = checkThree(0, 1, 2); if (w) return w;
        w = checkThree(3, 4, 5); if (w) return w;
        w = checkThree(6, 7, 8); if (w) return w;
        // Check columns
        w = checkThree(0, 3, 6); if (w) return w;
        w = checkThree(1, 4, 7); if (w) return w;
        w = checkThree(2, 5, 8); if (w) return w;
        // Check diagonals
        w = checkThree(0, 4, 8); if (w) return w;
        w = checkThree(2, 4, 6); if (w) return w;
        // Check draw
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) return 0;
        }
        return 3; // draw
    }

    int playerMove(int idx) {
        if (idx < 0 || idx > 8) return -1;
        if (board[idx] != 0) return -1;
        board[idx] = 1;
        return checkWinner();
    }

    int computerMove() {
        if (checkWinner()) return -1;
        
        // Win if possible
        int mv = findWinningMove(2);
        if (mv != -1) {
            board[mv] = 2;
            return checkWinner();
        }
        
        // Block player
        mv = findWinningMove(1);
        if (mv != -1) {
            board[mv] = 2;
            return checkWinner();
        }
        
        // Center
        if (board[4] == 0) {
            board[4] = 2;
            return checkWinner();
        }
        
        // Corners
        int corners[4] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            if (board[corners[i]] == 0) {
                board[corners[i]] = 2;
                return checkWinner();
            }
        }
        
        // First empty
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = 2;
                return checkWinner();
            }
        }
        
        return checkWinner();
    }

    void displayBoard() const {
        cout << "\n\n";
        cout << "     |     |     \n";
        for (int i = 0; i < 3; i++) {
            cout << "  " << getSymbol(i * 3) << "  |  " << getSymbol(i * 3 + 1) << "  |  " << getSymbol(i * 3 + 2) << "  \n";
            if (i < 2) {
                cout << "-----------+-----------+-----------\n";
            }
        }
        cout << "     |     |     \n\n";
    }

    void displayBoardWithNumbers() const {
        cout << "\nPosition numbers:\n\n";
        cout << "     |     |     \n";
        for (int i = 0; i < 3; i++) {
            cout << "  " << i * 3 << "  |  " << i * 3 + 1 << "  |  " << i * 3 + 2 << "  \n";
            if (i < 2) {
                cout << "-----------+-----------+-----------\n";
            }
        }
        cout << "     |     |     \n\n";
    }

private:
    char getSymbol(int idx) const {
        if (board[idx] == 1) return 'X';
        if (board[idx] == 2) return 'O';
        return ' ';
    }
};

int main() {
    TicTacToe game;
    int result = 0;

    cout << "\n========================================\n";
    cout << "       TIC TAC TOE - C++ VERSION\n";
    cout << "========================================\n";
    cout << "You are X, Computer is O\n";

    while (true) {
        game.displayBoardWithNumbers();
        game.displayBoard();

        if (result == 1) {
            cout << "You won! Congratulations!\n";
            break;
        } else if (result == 2) {
            cout << "Computer wins! Try again!\n";
            break;
        } else if (result == 3) {
            cout << "It's a draw!\n";
            break;
        } else {
            cout << "Your turn - Enter position (0-8): ";
            int move;
            cin >> move;

            if (move < 0 || move > 8) {
                cout << "Invalid position! Enter a number between 0 and 8.\n";
                continue;
            }

            result = game.playerMove(move);

            if (result == -1) {
                cout << "That position is already taken or invalid!\n";
                result = 0;
                continue;
            }

            game.displayBoard();

            if (result == 1) {
                cout << "You won! Congratulations!\n";
                break;
            } else if (result == 3) {
                cout << "It's a draw!\n";
                break;
            }

            cout << "Computer is thinking...\n";
            result = game.computerMove();

            if (result == 0) {
                cout << "Computer made its move!\n";
            }
        }
    }

    cout << "\n========================================\n";
    cout << "Play again? (yes/no): ";
    string answer;
    cin >> answer;

    if (answer == "yes" || answer == "y") {
        game.resetBoard();
        main();
    }

    cout << "Thanks for playing!\n";
    cout << "========================================\n\n";

    return 0;
}
