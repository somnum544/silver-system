
#include <stdio.h>
#include <stdlib.h>


#define GREEN "\e[0;32m"
#define RED "\e[0;31m"
#define SIZE 8


char** create_board();
char** place_pieces(char** board, const char black_pieces[], const char white_pieces[]);
char** make_move(board);
int check_valid_input(char *move);

//TODO make move, check valid move, 



int main(void){
    
    const char black_pieces[] = {'♜', '♞', '♝', '♛', '♚', '♝', '♞', '♜'};
    const char white_pieces[] = {'♖', '♘', '♗', '♕', '♔', '♗', '♘', '♖'};
    
    char** board = create_board();  
    place_pieces(board, black_pieces, white_pieces);
    
    // Print the board
    print_board(board);

    while (1){
    
        char move[5];
        scanf("%s", move);
        
        //check_correct_input
        //check_valid_move
        //make_move(move);
        //print_board(board);

    }

    // Free memory after use
    for (int i = 0; i < SIZE; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}







char** make_move(board){}
int check_valid_input(char *move){
    
}

void print_board(char **board){

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

char** place_pieces(char** board, const char black_pieces[], const char white_pieces[]){
    
    // Place black pieces
    for(int i = 0; i < SIZE; i++){
        board[0][i] = black_pieces[i];
        board[1][i] = '♟';
    }
    
    // Place white pieces
    for(int i = 0; i < SIZE; i++){
        board[7][i] = white_pieces[i];
        board[6][i] = '♙';
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