#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int Marime = 9;

// Functie pentru a afisa tabloul Sudoku
void afisareSudoku(const vector<vector<int>>& board) {
    for (int i = 0; i < Marime; ++i) {
        if (i % 3 == 0 && i != 0) {
            cout << "------+-------+------\n";
        }
        for (int j = 0; j < Marime; ++j) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

// Functie pentru a verifica daca o valoare poate fi plasata intr-o anumita pozitie pe tablou
bool esteValid(const vector<vector<int>>& board, int row, int col, int num) {
    // Verificam daca valoarea num se afla deja in randul respectiv
    for (int i = 0; i < Marime; ++i) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Verificam daca valoarea num se afla deja in coloana respectiva
    for (int i = 0; i < Marime; ++i) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Verificam daca valoarea num se afla deja in subgrid-ul 3x3 corespunzator
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Functie pentru a rezolva jocul de Sudoku
bool rezolvaSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < Marime; ++row) {
        for (int col = 0; col < Marime; ++col) {
            if (board[row][col] == 0) { // Spatiu gol
                for (int num = 1; num <= 9; ++num) {
                    if (esteValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (rezolvaSudoku(board)) {
                            return true;
                        }
                        board[row][col] = 0; // Daca nu putem gasi o solutie valida, reinitializam spatiul
                    }
                }
                return false; // Daca nu putem gasi nicio valoare valida, intoarcem fals
            }
        }
    }
    return true; // Daca tabloul este completat, intoarcem adevarat
}

// Functie pentru a umple tabloul de sudoku cu numere aleatoare
void umpleSudokuRandom(vector<vector<int>>& board) {
    // Initializare pentru generarea de numere aleatoare
    srand(time(0));

    for (int i = 0; i < Marime; ++i) {
        for (int j = 0; j < Marime; ++j) {
            if (rand() % 4 == 0) { // Setam o celula la intamplare cu un numar intre 1 si 9
                int num = rand() % 9 + 1;
                if (esteValid(board, i, j, num)) {
                    board[i][j] = num;
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> board(Marime, vector<int>(Marime, 0));

    umpleSudokuRandom(board);

    cout << "Tabloul Sudoku generat aleatoriu:\n";
    afisareSudoku(board);

    cout << "\nSolutia:\n";
    if (rezolvaSudoku(board)) {
        afisareSudoku(board);
    }
    else {
        cout << "Nu exista o solutie valida pentru acest tablou Sudoku!\n";
    }

    return 0;
}
