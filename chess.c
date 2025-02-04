// ahojky :PP
// BALLS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 8
char** place_pieces(char** board, const char black_pieces[], const char white_pieces[]){
    // Place black pieces
    for(int i = 0; i < SIZE; i++){
        board[0][i] = black_pieces[i];
        board[1][i] = 'p';
    }
    
    // Place white pieces
    for(int i = 0; i < SIZE; i++){
        board[7][i] = white_pieces[i];
        board[6][i] = 'P';
    }

    for(int i = 2; i<6; i++){
        for(int j = 0; j<SIZE; j++){
            board[i][j] = '_';
        }
    }
    return board;
}

char** create_board(){
    char** board = malloc(SIZE * sizeof(int*));  // Allocate space for the rows
    for (int i = 0; i < SIZE; i++){
        board[i] = malloc(SIZE * sizeof(int));  // Allocate space for columns
    }
    
    return board;
}

int main(void){
    
    const char black_pieces[] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    const char white_pieces[] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    
    char** board = create_board();  
    place_pieces(board, black_pieces, white_pieces);
    
    // Print the board
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    // Free memory after use
    for (int i = 0; i < SIZE; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}
