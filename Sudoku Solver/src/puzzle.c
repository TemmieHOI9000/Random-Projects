#include "sudoku.h"

Sudoku* createSudoku(Square*** squares, Box** boxes){
    Sudoku * sudoku;
    sudoku = malloc(sizeof(Sudoku));

    sudoku -> squares = squares;
    sudoku -> boxes = boxes;

    return sudoku;
}

int updateSudoku(Square*** sudoku, int row, int column){
    int x;
    int number = sudoku[row][column] -> number;

    for (x = 0; x < SIZE_ROWS; x++){
        if (sudoku[x][column] -> possible[number - 1] == 0){
            sudoku[x][column] -> solvable--;
        }
        sudoku[x][column] -> possible[number - 1] = 1;
    }

    for (x = 0; x < SIZE_COLUMNS; x++){
        if (sudoku[row][x] -> possible[number - 1] == 0){
            sudoku[row][x] -> solvable--;
        }
        sudoku[row][x] -> possible[number - 1] = 1;
    }

    return 1;
}

Sudoku* setUpPuzzle(int** puzzle){
    Square*** sudoku;
    Box** boxes;
    int i, j, x;
    int currentBox = 0;

    sudoku = (Square***)malloc(sizeof(Square**)*9);
    boxes = createBoxes();

    /* loop through rows */
    for (i = 0; i < SIZE_ROWS; i++){
        // malloc space for each row
        sudoku[i] = (Square**)malloc(sizeof(Square*)*9);
        /* loop through cols*/
        for (j = 0; j < SIZE_COLUMNS; j++){
            // malloc space for each square
            sudoku[i][j] = (Square*)malloc(sizeof(Square)*9);
            // assign number to sudoku adt
            sudoku[i][j] -> number = puzzle[i][j];
            // assign row, column, and solvable to each square
            sudoku[i][j] -> row = i;
            sudoku[i][j] -> col = j;
            sudoku[i][j] -> solvable = 9;

            boxes[currentBox] -> squares[boxes[currentBox] -> numbers] = sudoku[i][j];
            sudoku[i][j] -> box = boxes[currentBox];
            boxes[currentBox] -> numbers++;

            for (x = 0; x < SIZE_ROWS; x++){
                sudoku[i][j] -> possible[x] = 0;
            }

            if (j == 2){
                currentBox++;
            }
            if (j == 5){
                currentBox++;
            }
        }

        currentBox -= 2;
        if (i == 2){
            currentBox = 3;
        }
        if (i == 5){
            currentBox = 6;
        }
    }

    /* loop through rows */
    for (i = 0; i < SIZE_ROWS; i++){
        /* loop through cols*/
        for (j = 0; j < SIZE_COLUMNS; j++){
            if (sudoku[i][j] -> number != 0){
                sudoku[i][j] -> solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return createSudoku(sudoku, boxes);
}

int checkPuzzle(Square*** sudoku, Box** boxes){
    int i, j, x;
    
    /* loop through rows */
    for (i = 0; i < SIZE_ROWS; i++){
        /* loop through cols*/
        for (j = 0; j < SIZE_COLUMNS; j++){
            if (sudoku[i][j] -> solvable == 1){
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);

                return 1; /* This means we have solved something and bypass
                             needing to run boxSingles which takes a lot of rss */
            } 
        }
    }

    if (boxSingles(sudoku, boxes)){
        return 1;
    }
    return checkRows(sudoku, boxes);
 }

int** createPuzzle(){
    int** puzzle;
    int i, j;
    int array[9][9] = {0, 0, 0,    5, 0, 0,    1, 6, 3,
                       0, 4, 9,    0, 1, 3,    5, 0, 7,
                       5, 0, 0,    6, 2, 0,    8, 0, 4,

                       4, 9, 0,    1, 0, 5,    3, 8, 2,
                       2, 1, 8,    0, 0, 0,    4, 0, 0,
                       0, 5, 0,    2, 0, 8,    9, 0, 0,

                       0, 0, 0,    0, 0, 0,    0, 0, 8,
                       0, 0, 5,    7, 0, 6,    2, 0, 0,
                       3, 0, 0,    9, 0, 0,    6, 0, 0 };
    
    puzzle = (int**)malloc(sizeof(int*)*9);

    for (i = 0; i < 9; i++){
        puzzle[i] = (int*)malloc(sizeof(int)*9);

        for (j = 0; j < 9; j++){
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void printPuzzle(Square*** puzzle){
    int i, j;

    printf("-------------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++){
        
        printf("|");
        /* print each row*/
        for (j = 0; j < SIZE_COLUMNS; j++){
            printf(" %d ", puzzle[i][j] -> number);
            if ((j + 1) % 3 == 0){
                printf("|");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0){
            printf("-------------------------------\n");
        }
    }
}