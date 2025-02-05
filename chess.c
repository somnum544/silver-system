#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAG "\e[0;35m"  // color for black pieces
#define YEL "\e[0;33m"  // color for white pieces
#define RST "\e[0m"  // default color (reset color)
#define SIZE 8

// TODO: make move, check valid move, 
void print_help();
char** create_board();
char** place_pieces(char** board, const char black_pieces[], const char white_pieces[]);
char** make_move(char **board, char *move);
int check_valid_input(char *move);
void print_board(char **board);
void convert_to_upper(char* input, int input_len);

    /*********************/
    /**      MAIN       */
    /*********************/

int main(void) {
    // black pieces will be displayed in terminal as upper letters, but with changed color
    const char black_pieces[] = {'r','n','b','q','k','r','n','b'};  // {'♜', '♞', '♝', '♛', '♚', '♝', '♞', '♜'};
    const char white_pieces[] = {'R','N','B','Q','K','R','N','B'};  // {'♖', '♘', '♗', '♕', '♔', '♗', '♘', '♖'};
    
    char** board = create_board();  
    place_pieces(board, black_pieces, white_pieces);
    
    // Print the board
    print_board(board);

    // Main loop
    while (1) {
        
        // Stores the move from the input
        char move[10];
        printf("Your move: ");
        scanf("%s", move);
        printf("\n");
        
        // converting move to upper-case, to avoid case sensitivity
        convert_to_upper(move, strlen(move));

        // Printing help for user
        if((strcmp(move, "--HELP")) == 0){
            print_help();
            continue;
        }

        // Ending the game
        if((strcmp(move, "EXIT")) == 0){
            printf("Thanks for playing!\n");
            for (int i = 0; i < SIZE; i++) {    // Memory cleanup
                free(board[i]);
            }
            free(board);
            
            return 0;
        }

        // Checking valid input
        if (!check_valid_input(move)) {
            printf("Invalid move format!\n");
            continue;
        }

        // Moving the piece
        make_move(board, move);
        print_board(board);
        printf("\n\n");
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

void print_help(){
    printf("Enter moves as [FROM][TO] with no spaces (E2E4)\n");
    printf("To exit the game type 'exit'\n");
    printf("To display help menu type '--help\n");
    printf("Enjoy the game!\n");
    printf("\n");
}

char** make_move(char** board, char *move) {
    const char squares[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    
    int column_from = move[0] - 'A';
    int row_from = 7 -  (move[1] - '1');
    int column_to = move[2] - 'A';
    int row_to = 7 - (move[3] - '1');

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
            
            // if-segment, for color recognition
            if (islower(board[i][j]) && board[i][j] != '_') {  // is a black piece
                printf("%s%c%s ", MAG, toupper(board[i][j]), RST);
            } 
            
            else if (isupper(board[i][j]) && board[i][j] != '_') {  // is a white piece
                printf("%s%c%s ", YEL, board[i][j], RST);
            } 
            
            else {  // is an underscore character
                printf("%c ", board[i][j]);
            }
            
        }
        printf("  | %d", SIZE - i);  // chessboard row number (right side)
        printf("\n");
    }
    printf("________________\n");
    printf("A B C D E F G H\n");  // chessboard colon letters (bottom side)
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
        for(int j = 0; j<SIZE; j++) {
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

void convert_to_upper(char* input, int input_len) {
    for (int i = 0; i < input_len; i++) {
        if (isalpha(input[i])) {
            input[i] = toupper(input[i]);
        }
    }
}
