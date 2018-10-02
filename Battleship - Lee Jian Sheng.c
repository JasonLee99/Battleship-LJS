/*
 ============================================================================
 Name        : Battleship.c
 Author      : Lee Jian Sheng
 Version     : Assignment
 Copyright   : Lee Jian Sheng @ 2018
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define LAT 10
#define LONG 10

#define P1 0
#define P2 1

#define NO_OF_SHIPS 5
#define CARRIER 'C'
#define BATTLESHIP 'B'
#define CRUISER 'R'
#define SUBMARINE 'S'
#define DESTROYER 'D'

#define SEA '~'
#define HIT 'X'
#define MISS '*'

typedef enum {
        C_length = 5,
        B_length = 4,
        R_Length = 3,
        S_Length = 3,
        D_Length = 2
} Ship_L;

typedef struct location{
        int row;
        int col;
} Location;

typedef struct square{
        char sym;
        Location pos;
} Square;

typedef struct seav{
        char sym;
        int length;
        char *ship_name;
} SeaV;

typedef struct player_stat{
        int no_of_hits;
} PlayerStat;

void start_board(Square board[][LONG]);
void show_board(Square board[][LONG], bool peg);
void place_ship(Square board[][LONG], SeaV ships[]);
void update_board(Square board[][LONG], Location tango);
bool isSunk(int sunk[][NO_OF_SHIPS], int player, char ship_sym);
bool convertStr(Location pos[], char *str, int length);
bool Win(PlayerStat players[], int player);
Location Fire(void);

int Hit(Square board[][LONG], Location tango);

void start_board(Square board[][LONG]){
    int i = 0, j = 0;

    for(i = 0; i < LAT; i++){
        for(j = 0; j < LONG; j++){
            board[i][j].sym = SEA;
            board[i][j].pos.row = i;
            board[i][j].pos.col = j;

        }
    }
}

void show_board(Square board[][LONG], bool peg){
    int i = 0, j = 0;

    puts("  0 1 2 3 4 5 6 7 8 9");

    for(i = 0; i < LAT; i++){
        printf("%d ", i);

        for(j = 0; j < LONG; j++){
            if(peg == true){
                printf("%c ", board[i][j].sym);

            }else{
                if(board[i][j].sym == HIT){
                    printf("%c ", HIT);

                }else if(board[i][j].sym == MISS){
                    printf("%c ", MISS);

                }else if(board[i][j].sym == SEA){
                    printf("%c ", SEA);

                }else{
                    printf("%c ", SEA);

                }
            }
        }
        putchar('\n');

    }
}

void place_ship(Square board[][LONG], SeaV ships[]){
    char str[11] = ""; //if bad input, print a few extra boards

    Location pos[5];
    bool Valid = false;

    for(int i = 0; i < NO_OF_SHIPS; i++){
        while(true){
            system("cls");
            show_board(board, true);
            printf("Place the %s across %d cells: \n", ships[i].ship_name, ships[i].length);
            printf("Enter the %d cells: ", ships[i].length);
            scanf("%s", str);

            if(convertStr(pos, str, ships[i].length)){
                Valid = true;

                for(int j = 0; j < ships[i].length; j++){
                    if(board[pos[j].row][pos[j].col].sym == SEA){
                        board[pos[j].row][pos[j].col].sym = ships[i].sym;

                    }else{
                        Valid = false;
                        printf("\nBad input!\n");

                        if(j != 0){
                            while(j >= 0){
                                board[pos[j].row][pos[j].col].sym = SEA;
                                j--;

                            }
                        break;

                        }
                    }
                }
            }else{
                Valid = false;
                printf("\nInvalid input!\n");
            }
            if(Valid == true){
                break;

            }
        }
    }
}

void update_board(Square board[][LONG], Location tango){
    switch(board[tango.row][tango.col].sym){
        case SEA:
            board[tango.row][tango.col].sym = MISS;
            break;
        case CARRIER:
        case BATTLESHIP:
        case CRUISER:
        case SUBMARINE:
        case DESTROYER:
            board[tango.row][tango.col].sym = HIT;
            break;
        case HIT:
        case MISS:
        default:
            break;
    }
}

bool isSunk(int sunk[][NO_OF_SHIPS], int player, char ship_sym){
    bool sank = false; //Less one hit already sink

    if(ship_sym == CARRIER){
        if(--sunk[player][0] == 0){
            printf("Player %d's carrier sank!\n", player + 1);
            return sank = true;

        }
    }else if(ship_sym == BATTLESHIP){
        if(--sunk[player][1] == 0){
            printf("Player %d's battleship sank!\n", player + 1);
            return sank = true;

        }
    }else if(ship_sym == CRUISER){
        if(--sunk[player][2] == 0){
            printf("Player %d's cruiser sank!\n", player + 1);
            return sank = true;

        }
    }else if(ship_sym == SUBMARINE){
        if(--sunk[player][3] == 0){
            printf("Player %d's submarine destroyed!\n", player + 1);
            return sank = true;

        }
    }else if(ship_sym == DESTROYER){
        if(--sunk[player][4] == 0){
            printf("Player %d's destroyer sank!\n", player + 1);
            return sank = true;

        }
    }
    return sank;

}


bool convertStr(Location pos[], char *str, int length){
    bool flag = true;
    int j = 0, k = 1;

    if(strlen(str)/2 == length){
        for(int i = 0; i < length; i++){
            if(isdigit(str[j]) && isdigit(str[k])){
                pos[i].row = str[j] - '0';
                pos[i].col = str[k] - '0';

                j += 2;
                k += 2;

            }else{
                flag = false;

            }
        }
    }else{
        flag = false;

    }
    return flag;

}


bool Win(PlayerStat players[], int player){
    bool winner = false;

    if(players[player].no_of_hits == 17){
        winner = true;

    }
    return winner;

}

Location Fire(void){
    Location tango;

    fflush(stdin);

    printf("Fire at: \n");
    scanf("%d %d", &tango.row, &tango.col);

    return tango;

}

int Hit(Square board[][LONG], Location tango){
    int hit = -2;

    switch(board[tango.row][tango.col].sym){
        case SEA:
            hit = 0;
            break;
        case CARRIER:
        case BATTLESHIP:
        case CRUISER:
        case SUBMARINE:
        case DESTROYER:
            hit = 1;
            break;
        case HIT:
        case MISS:
        default:
            hit = -1;
            break;
    }
    return hit;

}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    PlayerStat players[2] = {
            {0},
            {0}
    };
    Square boardP1[LAT][LONG];
    Square boardP2[LAT][LONG];

    Location tango;

    SeaV ships[NO_OF_SHIPS] = {
            {'C', 5, "Carrier"},
            {'B', 4, "Battleship"},
            {'R', 3, "Cruiser"},
            {'S', 3, "Submarine"},
            {'D', 2, "Destroyer"}
    };

    int sunk[2][NO_OF_SHIPS] = {
            {5, 4, 3, 3, 2},
            {5, 4, 3, 3, 2}
    };

    int player = 0;
    int shoot = 0;

    bool hasSunk = false;

    char ship_sym = '\0';

    start_board(boardP1);
    start_board(boardP2);

    printf("P1:\n"); //No print
    place_ship(boardP1, ships);

    printf("P2:\n"); //No print
    place_ship(boardP2, ships);

    system("cls");

    while(true){
        printf("P%d: \n", player + 1);

        if(player == P1){
            puts("P2 board:\n");
            show_board(boardP2, false);
            puts("P1 turn\n");

            do{
                tango = Fire();
                shoot = Hit(boardP2, tango);

                if(shoot == -1){
                    puts("Try again!\n");

                }
            }while(shoot == -1);

            ship_sym = boardP2[tango.row][tango.col].sym;

        }else if(player == P2){
            puts("P1 board:\n");
            show_board(boardP1, false);
            puts("P2 turn\n");

            if(hasSunk){
                hasSunk = false;
            }


            do{
                tango = Fire();
                shoot = Hit(boardP1, tango);

                if(shoot == -1){
                    puts("Try again!\n");

                }
            }while(shoot == -1);

            ship_sym = boardP1[tango.row][tango.col].sym;

        }

        if(shoot == 1){
            printf("HIT!\n");

            players[player].no_of_hits++;

            if(player == 1){
                hasSunk = isSunk(sunk, !player, ship_sym);

            }else if(player == 0){
                isSunk(sunk, !player, ship_sym);

            }
        }else{
            puts("MISS!\n");

        }
        if(player == 0){
            update_board(boardP2, tango);

        }else{
            update_board(boardP1, tango);

        }

        if(Win(players, player) == true){
            printf("\nP%d wins!\n", player + 1);

            break;
        }

        if(player == 0){
            player = 1;
        }else if(player == 1){
            player = 0;
        }
        printf("\n");

    }
    return EXIT_SUCCESS;

}
