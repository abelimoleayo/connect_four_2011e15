/*
    Author: Imoleayo Abel
    E15 Final Project
    December 11, 2011
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NROWS 6
#define NCOLS 7
#define p1char 'X'
#define p2char 'O'


// Prints out the game board with the current layout of pieces
//
// board: 2-dimensional array
void print_board(char board[NROWS][NCOLS]) {
    int i, j;
    printf("\n  1   2   3   4   5   6   7\n");      // print column numbers
    for (i=0; i<NROWS; ++i) {
        printf("+---+---+---+---+---+---+---+\n");  // print portion of grid between rows
        for (j=0; j<NCOLS; ++j) {           // print each character in current row and
            printf("| %c ", board[i][j]);   // print portion of grid in the row
        }                                  
        printf("|\n");
    }
    printf("+---+---+---+---+---+---+---+\n");
}


// Creates a 2-dimensional array of spaces
//
// board: 2-dimensional array 
void init_board(char board[NROWS][NCOLS]) {
    int i, j;
    for (i=0; i<NROWS; ++i) {
        for (j=0; j<NCOLS; ++j) {
            board[i][j] = ' ';
        }
    }
}


/* 
Determines if there are "num" pieces of a given type ('X' or 'O') connected
and also whether it is possible to get 4 of that type in a row at the given location

Returns:
    0: if there are NOT num in a line and it is NOT possible to get 4 in a line
    1: if there are num in a line and it is possible to get 4 in a line
NOTE: "possible to get 4 in a line" refers to 4 in a line in which there are
      num in a line already

board: 2-dimensional array
pchar: character of triggering player ('X' or 'O')
row:   row index in board
col:   column index in board
num:   number in a row being searched for
*/
int has_won(char board[NROWS][NCOLS], char pchar, int row, int col, int num) {
    int i = 0;
    int j = col;
    int accum = 0;      // accum stores the current numbber of pchar in a line seen
    int posaccum = 0;   // posaccum is for computer_move and is used to determine if
                        // it is possible for the computer to get 4 in a row
    int accumchk = 0;   // accumchk stores whether num in a line were found in the
                        // set of pchars and ' 's currently being checked

    // check column
    while (i<NROWS) {   // check each value in given column
        if ((board[i][col] == pchar) || (board[i][col] == ' ')) {
            posaccum++;     // as long as the stored character does not belong to the
                            // other player, the possible number in a row is incremented
            if (board[i][col] == pchar) {
                accum++;    // if the stored character is pchar, the number in a row is
                            // incremented
                if (accum >= num) {
                    accumchk = 1;
                }
            } else {    // a char other than pchar was seen
                accum = 0;
            }

            if ((posaccum >= 4) && (accumchk == 1)) {   // there are num in a row and it
                return 1;                               // is possible to get 4 in a row
            }
        } else {        // the other player's cahracter is seen
            accum = 0;
            posaccum = 0;
            accumchk = 0;
        }
        i++;
    }

    // check row
    i = row; j = 0; accum = 0; posaccum = 0; accumchk = 0;
    while (j<NCOLS) {   // check each value in given row
        if ((board[row][j] == pchar) || (board[row][j] == ' ')) {
            posaccum++; // as long as the stored character does not belong to the
                        // other player, the possible number in a row is incremented
            if (board[row][j] == pchar) {
                accum++;    // if the stored character is pchar, the number in a row is
                            // incremented
                if (accum >= num) {
                    accumchk = 1;
                }
            } else {    // a char other than pchar was seen
                accum = 0;
            }
            if ((posaccum >= 4) && (accumchk == 1)) {   // there are num in a row and it
                return 1;                               // is possible to get 4 in a row
            }
        } else {        // the other player's cahracter is seen
            accum = 0;
            posaccum = 0;
            accumchk = 0;
        }
        j++;
    }

    // check downward-sloping diagonal
    i = row; j = col; accum = 0; posaccum = 0; accumchk = 0;
    while (i>0 && j>0) {    // find upper-left entry of given diagonal
        i--;
        j--;
    }
    while (i<NROWS && j<NCOLS) { // check each value in given diagonal
        if ((board[i][j] == pchar) || (board[i][j] == ' ')) {
            posaccum++;     // as long as the stored character does not belong to the
                            // other player, the possible number in a row is incremented
            if (board[i][j] == pchar) {
                accum++;    // if the stored character is pchar, the number in a row is
                            // incremented
                if (accum >= num) {
                    accumchk = 1;
                }
            } else {    // a char other than pchar was seen
                accum = 0;
            }
            if ((posaccum >= 4) &&  (accumchk == 1)) {  // there are num in a row and it 
                return 1;                               // is possible to get 4 in a row
            }
        } else {        // the other player's cahracter is seen
            accum = 0;
            posaccum = 0;
            accumchk = 0;
        }
        i++;
        j++;
    }

    // check upward-sloping diagonal
    i=row; j=col; accum=0; posaccum = 0; accumchk = 0;
    while (i>0 && j<NCOLS-1) {  // find upper-right entry of given diagonal
        i--;
        j++;
    }
    while (i<NROWS && j>=0) {   // check each value in given diagonal
        if ((board[i][j] == pchar) || (board[i][j] == ' ')) {
            posaccum++;     // as long as the stored character does not belong to the
                            // other player, the possible number in a row is incremented
            if (board[i][j] == pchar) {
                accum++;    // if the stored character is pchar, the number in a row is
                            // incremented
                if (accum >= num) {
                    accumchk = 1;
                }
            } else {    // a char other than pchar was seen
                accum = 0;
            }
            if ((posaccum >= 4) && (accumchk == 1)) {   // there are num in a row and it
                return 1;                               // is possible to get 4 in a row
            }
        } else {        // the other player's cahracter is seen
            accum = 0;
            posaccum = 0;
            accumchk = 0;
        }
        i++;
        j--;
    }

    return 0; // don't go here or no winner (depending on situation)
}


// For any given column, finds the lowest open row
//
// board: 2-dimensional array
// col: column index in board
int row_for_column(char board[NROWS][NCOLS], int col) {
    int i=0;
    for (i=NROWS-1; i>=0; i--) {
        if (board[i][col] == ' ') {
            return i;   // return index of lowest open row
        }
    }
    return -1;  // no row is open
}


// Gets input from player and returns it if it is valid
//
// board: 2-dimensional array
int player_move(char board[NROWS][NCOLS]) {
    while (1) {
        char c = ' ';
        char inp = getchar();
        while (c != '\n') { // take only first character entered and ignore others
            c = getchar();
        }
        if ((inp >= '1') && (inp <= '7')) { // if input is a number in the valid range
            if (row_for_column(board, atoi(&inp) - 1) != -1) { // if column is not
                return atoi(&inp) - 1;                         // full
            } else {
                printf("Error: Column is Full: ");
            }
        } else {
            printf("Error: Invalid Column: ");
        }
    }  
}


// Computer chooses where to move
//
// board: 2-dimensional array
int computer_move(char board[NROWS][NCOLS]) {
    int row, col;

    //(1) Can I win?
    for (col=0; col<NCOLS; col++) {     // checks each column
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p2char;   // insert p2char temporarily
            if (has_won(board, p2char, row, col, 4) == 1) { // if computer can win
                board[row][col] = ' ';  // remove p1char if player can win
                return col;
            }
            board[row][col] = ' ';      // remove p1char if player can't win
        }
    }

    //(2) Can player win?
    for (col=0; col<NCOLS; col++) {     // checks each column
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p1char;   // insert p1char temporarily
            if (has_won(board, p1char, row, col, 4) == 1) { // if player can win
                board[row][col] = ' ';  // remove p1char if player can win
                return col;
            }
            board[row][col] = ' ';      // remove p1char if player can't win
        }
    }

    //(3) Can I stop player from getting 3 in a row?
    srand(time(0));     // use current time to choose index in list of random numbers
    int colselect = rand() % 7;     // randomly select column
    for (col=colselect; col<NCOLS; col++) { // check columns up through 7
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p1char;       // insert p1char temporarily
            if (has_won(board, p1char, row, col, 3) == 1) { // if player can get 3
                board[row][col] = ' ';      // remove p1char if player can get 3
                if (row-1 < 0) {    // if move will fill column
                    return col;
                } else {    // move will not fill column
                    board[row-1][col] = p1char;
                    if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                        // checks to see if move will allow player to win next turn
                        board[row-1][col] = ' ';
                    } else {    // if move will not allow player to win
                        board[row-1][col] = ' ';
                        return col;
                    }
                }
            }
            board[row][col] = ' ';
        }
    }
    for (col=0; col<colselect; col++) { // check columns from 0 up to selected one
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p1char;   // insert p1char temporarily
            if (has_won(board, p1char, row, col, 3) == 1) { // if player can get 3
                board[row][col] = ' ';  // remove p1char if player can get 3
                if (row-1 < 0) {    // if move will fill column
                    return col;
                } else {            // move will not fill column
                    board[row-1][col] = p1char;
                    if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                        // checks to see if move will allow player to win next turn
                        board[row-1][col] = ' ';
                    } else {    // if move will not allow player to win
                        board[row-1][col] = ' ';
                        return col;
                    }
                }
            }
            board[row][col] = ' ';
        }
    }

    //(4) Can I get 3 in a row?
    srand(time(0));     // use current time to choose index in list of random numbers
    colselect = rand() % 7;     // randomly select column
    for (col=colselect; col<NCOLS; col++) { // check columns up through 7
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p2char;       // insert p2char temporarily
            if (has_won(board, p2char, row, col, 3) == 1) { // if computer can get 3
                board[row][col] = ' ';      // remove p2char if computer can get 3
                if (row-1 < 0) {    // if move will fill column
                    return col;
                } else {            // move will not fill column
                    board[row-1][col] = p1char;
                    if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                        // checks to see if move will allow player to win next turn
                        board[row-1][col] = ' ';
                    } else {    // if move will not allow player to win
                        board[row-1][col] = ' ';
                        return col;
                    }
                }
            }
            board[row][col] = ' ';
        }
    }
    for (col=0; col<colselect; col++) { // check columns from 0 up to selected one
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p2char;   // insert p2char temporarily
            if (has_won(board, p2char, row, col, 3) == 1) { // if computer can get 3
                board[row][col] = ' ';  // remove p2char if computer can get 3
                if (row-1 < 0) {    // if move will fill column
                    return col;
                } else {            // move will not fill column
                    board[row-1][col] = p1char;
                    if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                        // checks to see if move will allow player to win next turn
                        board[row-1][col] = ' ';
                    } else {    // if move will not allow player to win
                        board[row-1][col] = ' ';
                        return col;
                    }
                }
            }
            board[row][col] = ' ';
        }
    }

    //(5) Can I get 2 in a row?
    srand(time(0));     // use current time to choose index in list of random numbers
    colselect = rand() % 7;     // randomly select column
    for (col=colselect; col<NCOLS; col++) { // check columns up through 7
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p2char;       // insert p2char temporarily
            if (has_won(board, p2char, row, col, 2) == 1) { // if computer can get 2
                board[row][col] = ' ';      // remove p2char if computer can get 2
                if (row-1 < 0) {    // if move will fill column
                    return col;
                } else {            // move will not fill column
                    board[row-1][col] = p1char;
                    if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                        // checks to see if move will allow player to win next turn
                        board[row-1][col] = ' ';
                    } else {    // if move will not allow player to win
                        board[row-1][col] = ' ';
                        return col;
                    }
                }
            }
            board[row][col] = ' ';
        }
    }
    for (col=0; col<colselect; col++) { // check columns from 0 up to selected one
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            board[row][col] = p2char;   // insert p2char temporarily
            if (has_won(board, p2char, row, col, 2) == 1) { // if computer can get 2
                board[row][col] = ' ';  // remove p2char if computer can get 2
                if (row-1 < 0) {    // if move will fill column
                    return col;
                } else {            // move will not fill column
                    board[row-1][col] = p1char;
                    if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                        // checks to see if move will allow player to win next turn
                        board[row-1][col] = ' ';
                    } else {    // if move will not allow player to win
                        board[row-1][col] = ' ';
                        return col;
                    }
                }
            }
            board[row][col] = ' ';
        }
    }  

    //(6) Go randomly without allowing player to win
    srand(time(0));     // use current time to choose index in list of random numbers
    colselect = rand() % 7;     // randomly select column
    for (col=colselect; col<NCOLS; col++) { // check columns up through 7
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            if (row-1 < 0) {    // if move will fill column
                return col;
            } else {            // move will not fill column
                board[row-1][col] = p1char;
                if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                    // checks to see if move will allow player to win next turn
                    board[row-1][col] = ' ';
                } else {    // if move will not allow player to win
                    board[row-1][col] = ' ';
                    return col;
                }
            }
        }
    }
    for (col=0; col<colselect; col++) { // check columns from 0 up to selected one
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            if (row-1 < 0) {    // if move will fill column
                return col;
            } else {            // move will not fill column
                board[row-1][col] = p1char;
                if ((has_won(board, p1char, row-1, col, 4) == 1)) {
                    // checks to see if move will allow player to win next turn
                    board[row-1][col] = ' ';
                } else {    // if move will not allow player to win
                    board[row-1][col] = ' ';
                    return col;
                }
            }
        }
    }

    //(7) Go randomly and cannot stop player from winning
    srand(time(0));     // use current time to choose index in list of random numbers
    colselect = rand() % 7;     // randomly select column
    for (col=colselect; col<NCOLS; col++) { // check columns up through 7
        row = row_for_column(board, col);   // gets relevant row index for column
        if (row > -1) { // if column is not full
            return col;
        }
    }
    for (col=0; col<colselect; col++) { // check columns from 0 up to selected one
        row = row_for_column(board, col);   // gets relevant index for column
        if (row > -1) {     // if column is not full
            return col;
        }
    }

    return -1;   // should never happen
}



int main() {

    // this defines the board to be a NROWSxNCOLS matrix of characters
    char board[NROWS][NCOLS];

    // fills the board with space (' ') characters
    init_board(board);

    // prints the blank board
    print_board(board);

    // store player names
    char* p1="Player1";
    char* p2="";

    // find out if 2 humans will play or if a human will play a computer
    printf ("How many human players? (1 or 2): ");
    char inp = ' ';
    while (1) {
        inp = getchar();
        getchar();
        if ((inp == '1') || (inp == '2')) {
            break;
        } else {
            printf("Error: Enter 1 or 2: ");
        }
    }

    if (inp == '2') {
        p2 = "Player2";
    } else {
        p2 = "Computer";
    }

    // the first player to go is chosen randomly
    // pturn is multiplied by -1 at the end of every turn
    //   1 indicates Player1's turn
    //  -1 indicates Player2's (or Computer's) turn 
    int pturn = 1;
    srand(time(0));
    int pselector = rand() % 2;
    if (pselector == 0) {
        pturn = 1;
    } else {
        pturn = -1;
    }

    // the main portion of the game is played within this while loop
    int pcol;
    int nmoves = 0;
    while (1) {
        if (pturn == 1) { // Player1 goes
            printf("%s: ", p1);
            pcol = player_move(board);
        } else { // Player2 goes
            printf("%s: ", p2);
            if (strcmp(p2,"Player2")==0) {
                pcol = player_move(board);
            } else { // Computer goes
                pcol = computer_move(board);
                printf("%d\n", pcol + 1);
            }
        }

        int prow = row_for_column(board, pcol); // find row index for position
                                                // selected
        // put correct character in chosen space
        if (pturn == 1) {
            board[prow][pcol] = p1char;
        } else {
            board[prow][pcol] = p2char;
        }

        print_board(board);

        // checks for victory caused by move and ends game if a player won
        if (pturn == 1) {
            if(has_won(board, p1char, prow, pcol, 4) == 1) {
                printf("%s Wins!\n", p1);
                return 0;
            }
        } else {
            if (has_won(board, p2char, prow, pcol, 4) == 1) {
                printf("%s Wins!\n", p2);
                return 0;
            }
        }

        // if 42 moves are made without a player winning, the board is filled and 
        // the game is a tie
        nmoves++;
        if (nmoves >= 42) {
            printf("The Game is a Tie\n");
            return 0;
        }

        pturn *= -1; // it becomes the other player's turn
    }
}
