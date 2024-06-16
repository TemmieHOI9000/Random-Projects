#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main(){
    int** puzzle;
    int progress = 0;
    Sudoku* sudokuWithArray;

    puzzle = createPuzzle();

    sudokuWithArray = setUpPuzzle(puzzle);

    printPuzzle(sudokuWithArray -> squares);

    while (UNSOLVED > 0){
        progress = checkPuzzle(sudokuWithArray -> squares, sudokuWithArray -> boxes);

        if (progress == 0){
            printf("\nFailed to solve the puzzle!\n\n");
            break;
        }
    }

    printf("\nSolution was FOUND!\n\n");

    printPuzzle(sudokuWithArray -> squares);

    return 0;
}