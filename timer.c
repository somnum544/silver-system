// ahoj frank

#include <stdio.h>
#include <time.h>
#include <conio.h> // For kbhit() and getch()
#include <windows.h> // For Sleep()

#define STATE_X 3  // line where Running/Stopped text appears
#define STATE_Y 17  // first letter of Running/Stopped text

#define FIRSTPLAYERLINE 5  // note that the first line in terminal has index 1
#define LASTTIMERCHAR 20  // column index of last char, for every 'playerN: ...' line
#define FIRSTTIMERCHAR 11

#define COLORAMOUNT 7  // size_t ig
#define CRESET "\e[0m"  // default color

const char* colors[COLORAMOUNT] = {
    "\e[0;31m",  // RED
    "\e[0;32m",  // GRN
    "\e[0;33m",  // YEL
    "\e[0;34m",  // BLU
    "\e[0;35m",  // MAG
    "\e[0;36m",  // CYN
    "\e[0;37m"   // WHT
};

void displayAllTimers(double* arrTimeElapsed, double maxTime, int isRunning, int playerAmount);
void editState(int isRunning);
void editElapsedTime(double* arrTimeElapsed, double currentElapsed, int playerIndex, double maxTime);
void printArrow(int playerIndex);
void hideArrow(int playerIndex);

void hideCursor() {  // AI generated snippet
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Hide the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void showCursor() {  // AI generated snippet
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;  // Show the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int main(int argc, char* argv[]) {
    /*********************/
    /**  INPUT HANDLING  */
    /*********************/

    hideCursor();

    if (argc < 3) {
        fprintf(stderr, "Provide valid arguments: playerAmount maxTime\n");
        return 1;
    }

    // 2 parameters: n.o. Players, max time per player
    unsigned int playerAmount = atoi(argv[1]);
    if (playerAmount < 1 || playerAmount > 9) {  // player limit
        fprintf(stderr, "Amount of players supported: 1 to 9\n");
        return 1;
    }
    double maxTime = atof(argv[2]);

    // allocating arr space, setting all players to maxTime
    // elapsed time - cas, ktory sa meria pocas vsetkych zastaveni a pusteni. Neaktualizuje sa instantne, ale az po zastaveni
    double* arrTimeElapsed = malloc(sizeof(double)*playerAmount);
    for (int k = 0; k < playerAmount; k++) {
        arrTimeElapsed[k] = 0.0;
    }
    
    /*********************/
    /**   Some Set-ups   */
    /*********************/

    clock_t startTime = 0;
    int isRunning = 0; // 0 = stopped, 1 = running
    int playerIndex = 0;

    system("cls");
    displayAllTimers(arrTimeElapsed, maxTime, isRunning, playerAmount);

    /*********************/
    /**   MAIN LOOP   */
    /*********************/ 
    

    while (1) {
        // if displayed time hits 00:00:00
        if (arrTimeElapsed[playerIndex] >= maxTime) {
            printf("\033[%d;1H", FIRSTPLAYERLINE + playerAmount); // moving cursor to the last line (because of proper location for printf below)
            printf("\nTime ran out! Ending the program.\n");
            break;
        }

        /**   KEY PRESSES   */
        if (kbhit()) { // Check if a key was pressed
            char ch = getch(); // Get the key
            
            if (ch == 'c' || ch == ' ') {  // player change
                if (isRunning) {
                    // While timer still running
                    arrTimeElapsed[playerIndex] += (double)(clock() - startTime) / CLOCKS_PER_SEC;
                    isRunning = 1;
                    hideArrow(playerIndex);
                    playerIndex = (playerIndex + 1) % playerAmount;  // to assure staying in range
                    startTime = clock();
                } else {
                    // While paused
                    startTime = clock();
                    isRunning = 0;
                    hideArrow(playerIndex);
                    playerIndex = (playerIndex + 1) % playerAmount;  // to assure staying in range
                    printArrow(playerIndex);  // so that arrow shows even when paused
                }
            }

            else if (ch == 's') { // Start/Stop
                if (isRunning) {
                    // Stop the stopwatch
                    arrTimeElapsed[playerIndex] += (double)(clock() - startTime) / CLOCKS_PER_SEC;
                    isRunning = 0;
                    editState(isRunning);

                } else {
                    // Start the stopwatch
                    startTime = clock();
                    isRunning = 1;
                    editState(isRunning);

                }

            } else if (ch == 'r') { // Reset
                for (int i = 0; i < playerAmount; i++) {
                    arrTimeElapsed[i] = 0.0;    
                }
                isRunning = 0;
                displayAllTimers(arrTimeElapsed, maxTime, isRunning, playerAmount);

            } else if (ch == 'q') { // Quit
                printf("\033[%d;1H", FIRSTPLAYERLINE + playerAmount); // moving cursor to the last line (because of proper location for printf below)
                printf("\nExiting program. Goodbye!\n");
                break;
            }
        }

        if (isRunning) {
            // Update the elapsed time display
            double currentElapsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;  // cas od posledneho zastavenia
            editElapsedTime(arrTimeElapsed, currentElapsed, playerIndex, maxTime);
        }

        Sleep(100); // Sleep for just 100ms to avoid high CPU usage
    }
    
    free(arrTimeElapsed);
    showCursor();
    return 0;
}

    /*********************/
    /**    FUNCTIONS    */
    /*********************/ 

void editState(int isRunning) {  // running/stopped
    if (isRunning) {
        printf("\033[%d;%dHRUNNING", STATE_X, STATE_Y);
    } else {
        printf("\033[%d;%dHSTOPPED", STATE_X, STATE_Y);
    }
}

void editElapsedTime(double* arrTimeElapsed, double currentElapsed, int playerIndex, double maxTime) {
    // time part
    double realTime = maxTime - arrTimeElapsed[playerIndex] - currentElapsed;
    int hours = (int)(realTime / 3600);
    int minutes = (int)(realTime / 60) % 60;
    double seconds = realTime - (hours * 3600) - (minutes * 60);
        
    printf("%s\033[%d;%dH%02d:%02d:%04.1f%s\n", colors[playerIndex % (COLORAMOUNT-1)], FIRSTPLAYERLINE + playerIndex, FIRSTTIMERCHAR, hours, minutes, seconds, CRESET);
    fflush(stdout);

    // arrow part
    printArrow(playerIndex);
}

void displayAllTimers(double* arrTimeElapsed, double maxTime, int isRunning, int playerAmount) {
    double seconds;
    int hours, minutes;

    //system("cls");
    printf("\033[2J");  // Clear screen
    printf("\033[H");   // Move cursor to the top-left corner

    printf("--- Stopwatch Program ---\n");
    printf("Press 's' to Start/Stop, 'c' to Switch player, 'r' to Reset, 'q' to Quit.\n");

    if (isRunning) { 
        printf("CURRENT STATE:  RUNNING\n\n"); 
    } else {
        printf("CURRENT STATE:  STOPPED\n\n");
    }

    for (int i = 0; i < playerAmount; i++) {

        hours = (int)(maxTime / 3600);
        minutes = (int)(maxTime / 60) % 60;
        seconds = maxTime - (hours * 3600) - (minutes * 60);
        
        printf("%sPlayer %d: %02d:%02d:%04.1f%s\n", colors[i % (COLORAMOUNT-1)], i+1, hours, minutes, seconds, CRESET);
    }

    fflush(stdout); // Force immediate display
}

// called when player changed, func hides the pointing arrow (prints space in the arrow's location)
void hideArrow(int playerIndex) {
    printf("\033[%d;%dH   ", FIRSTPLAYERLINE + playerIndex, LASTTIMERCHAR + 2);  // moving the cursor at L, C; arrow pointing at current clock
    fflush(stdout);
}

void printArrow(int playerIndex) {
    printf("\033[%d;%dH <<", FIRSTPLAYERLINE + playerIndex, LASTTIMERCHAR + 2);  // moving the cursor at L, C; arrow pointing at current clock
    fflush(stdout);
}