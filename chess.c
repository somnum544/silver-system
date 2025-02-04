#include <stdio.h>
#include <stdlib.h>

#define GREEN "\e[0;32m"
#define RED "\e[0;31m"
#define SIZE 8

// TODO: make move, check valid move, 

char** create_board();
char** place_pieces(char** board, const char black_pieces[], const char white_pieces[]);
char** make_move(board);
int check_valid_input(char *move);
void print_board(char **board);


    /*********************/
    /**      MAIN       */
    /*********************/

int main(void) {
    const char black_pieces[] = {'♜', '♞', '♝', '♛', '♚', '♝', '♞', '♜'};
    const char white_pieces[] = {'♖', '♘', '♗', '♕', '♔', '♗', '♘', '♖'};
    
    char** board = create_board();  
    place_pieces(board, black_pieces, white_pieces);
    
    // Print the board
    print_board(board);

    // Main loop
    while (1) {
        char move[5];
        scanf("%s", move);

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
    
    // Index of squared moved FROM
    int index_curr = 0;
    for (int i = 0; i < SIZE; i++) {
        if(move[0] == squares[i]) {
            index_curr = i;
        }
    }

    // Index of squared moved TO
    int index_next = 0;
    for (int i = 0; i < SIZE; i++) {
        if(move[2] == squares[i]) {
            index_next = i;
        }
    }

    // Moving the piece
    board[index_next][move[3] - 1] = board[index_curr][move[1] - 1];
    
    // Clearing square moved from
    board[index_curr][move[1] - 1] = '_';
    return board;
}

int check_valid_input(char *move) {
    
    if (('A' <= (move[0] && move[2] >= 'H')) && (1 <= (move[1] && move[3]) >= 8)) return 1;
    return 0;
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
        board[1][i] = '♟';
    }
    
    // Place WHITE pieces
    for(int i = 0; i < SIZE; i++) {
        board[7][i] = white_pieces[i];
        board[6][i] = '♙';
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
    char** board = malloc(SIZE * sizeof(int*));  // Allocate space for the rows
    for (int i = 0; i < SIZE; i++){
        board[i] = malloc(SIZE * sizeof(int));  // Allocate space for columns
    }
    
    return board;
}