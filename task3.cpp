#include <iostream>
using namespace std;

class SudokuSolver {
private:
    int board[9][9];

public:
    SudokuSolver(int inputBoard[9][9]) {
        // Copy the input board into the class member board
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = inputBoard[i][j];
            }
        }
    }

    bool isValid(int row, int col, int num) {
        // Check if 'num' can be placed at board[row][col]
        for (int i = 0; i < 9; i++) {
            // Check the row and column
            if (board[row][i] == num || board[i][col] == num)
                return false;

            // Check the 3x3 subgrid
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num)
                return false;
        }
        return true;
    }

    bool solveSudoku() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    for (int num = 1; num <= 9; num++) { // Try numbers from 1 to 9
                        if (isValid(i, j, num)) {
                            board[i][j] = num;
                            if (solveSudoku()) {
                                return true;
                            }
                            board[i][j] = 0; // Backtrack
                        }
                    }
                    return false; // Trigger backtracking
                }
            }
        }
        return true; // Solved if no empty cells
    }

    void printBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j] << " ";
                if ((j + 1) % 3 == 0 && j < 8) {
                    cout << "| "; // Print grid separators for better readability
                }
            }
            cout << endl;
            if ((i + 1) % 3 == 0 && i < 8) {
                cout << "-----------------------" << endl; // Horizontal grid separator
            }
        }
    }
};

int main() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver(board);

    cout << "Original Sudoku:" << endl;
    solver.printBoard();

    if (solver.solveSudoku()) {
        cout << "\nSolved Sudoku:" << endl;
        solver.printBoard();
    } else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}