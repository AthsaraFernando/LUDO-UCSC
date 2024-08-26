#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

// Define a structure to represent a piece
struct Piece {
    int pieceid;
    int current_position;
    int starting_position;
    int no_captured;
    int clockwise;
    int approach_position;
    int approach_counter;
    int six_counter;
};

// Define a structure to represent a player
struct Player {
    char playerid;
    struct Piece pieces[4];
};

// Function prototypes
void initialize_random();
void initialize_players(struct Player players[]);
void move_piece_forward(struct Player *player, int piece_index, int steps);
void print_game_state(struct Player players[]);
int roll_dice();
void determine_player_order(struct Player players[], int order[]);

#endif

