#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN "\e[0;32m"
#define RED "\e[0;31m"
#define SIZE 8

// TODO: make move, check valid move, 

char** create_board();
char** place_pieces(char** board, const char black_pieces[], const char white_pieces[]);
char** make_move(char **board, char *move);
int check_valid_input(char *move);
void print_board(char **board);


    /*********************/
    /**      MAIN       */
    /*********************/

int main(void) {
    const char black_pieces[] = {'r','n','b','q','k','r','n','b'}; //{'♜', '♞', '♝', '♛', '♚', '♝', '♞', '♜'};
    const char white_pieces[] ={'R','N','B','Q','K','R','N','B'}; //{'♖', '♘', '♗', '♕', '♔', '♗', '♘', '♖'};
    
    char** board = create_board();  
    place_pieces(board, black_pieces, white_pieces);
    
    // Print the board
    print_board(board);

    // Main loop
    while (1) {
        // Stores the move from the input
        char move[5];
        scanf("%s", move);
        // Checking valid input
        if (!check_valid_input(move)) {
            printf("Invalid move format");
            continue;
        }
        // Moving the piece
        make_move(board, move);
        print_board(board);
    }

    // Free memory after use
    for (int i = 0; i < SIZE; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}

    /*********************/
    /**    FUNCTIONS    */
    /*********************/

char** make_move(char** board, char *move) {
    const char squares[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    
    int column_from = move[0] - 'A';
    int row_from = move[1] - '1';
    int column_to = move[2] - 'A';
    int row_to = move[3] - '1';

    board[row_to][column_to] = board[row_from][column_from];
    board[row_from][column_from] = '_';

    return board;
}

int check_valid_input(char *move) {
    
    return strlen(move) == 4 &&
           move[0] >= 'A' && move[0] <= 'H' &&
           move[1] >= '1' && move[1] <= '8' &&
           move[2] >= 'A' && move[2] <= 'H' &&
           move[3] >= '1' && move[3] <= '8';
}

void print_board(char **board) {

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

char** place_pieces(char** board, const char black_pieces[], const char white_pieces[]) {
    
    // Place BLACK pieces
    for(int i = 0; i < SIZE; i++) {
        board[0][i] = black_pieces[i];
        board[1][i] = 'p';     //♟
    }
    
    // Place WHITE pieces
    for(int i = 0; i < SIZE; i++) {
        board[7][i] = white_pieces[i];
        board[6][i] = 'P';       //♙
    }

    // printing BLANK chars
    for(int i = 2; i<6; i++) {
        for(int j = 0; j<SIZE; j++){
            board[i][j] = '_';
        }
    }
    return board;
}

char** create_board() {
    char** board = malloc(SIZE * sizeof(char*));  // Allocate space for the rows
    for (int i = 0; i < SIZE; i++){
        board[i] = malloc(SIZE * sizeof(char));  // Allocate space for columns
    }
    
    return board;
}