#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Seed the random number generator once at the start of the program
void initialize_random() {
    srand(time(NULL)); // Seed with current time
}

void initialize_players(struct Player players[]) {
    // Initialize Player R (Red)
    players[0].playerid = 'R';
    for (int i = 0; i < 4; i++) {
        players[0].pieces[i].pieceid = i;
        players[0].pieces[i].current_position = 28;
        players[0].pieces[i].starting_position = 28;
        players[0].pieces[i].no_captured = 0;
        // players[0].pieces[i].clockwise is not initialized here
        players[0].pieces[i].approach_position = 26;
        players[0].pieces[i].approach_counter = 0;
        players[0].pieces[i].six_counter = 0;
    }

    // Initialize Player G (Green)
    players[1].playerid = 'G';
    for (int i = 0; i < 4; i++) {
        players[1].pieces[i].pieceid = i;
        players[1].pieces[i].current_position = 41;
        players[1].pieces[i].starting_position = 41;
        players[1].pieces[i].no_captured = 0;
        // players[1].pieces[i].clockwise is not initialized here
        players[1].pieces[i].approach_position = 39;
        players[1].pieces[i].approach_counter = 0;
        players[1].pieces[i].six_counter = 0;
    }

    // Initialize Player Y (Yellow)
    players[2].playerid = 'Y';
    for (int i = 0; i < 4; i++) {
        players[2].pieces[i].pieceid = i;
        players[2].pieces[i].current_position = 2;
        players[2].pieces[i].starting_position = 2;
        players[2].pieces[i].no_captured = 0;
        // players[2].pieces[i].clockwise is not initialized here
        players[2].pieces[i].approach_position = 0;
        players[2].pieces[i].approach_counter = 0;
        players[2].pieces[i].six_counter = 0;
    }

    // Initialize Player B (Blue)
    players[3].playerid = 'B';
    for (int i = 0; i < 4; i++) {
        players[3].pieces[i].pieceid = i;
        players[3].pieces[i].current_position = 15;
        players[3].pieces[i].starting_position = 15;
        players[3].pieces[i].no_captured = 0;
        // players[3].pieces[i].clockwise is not initialized here
        players[3].pieces[i].approach_position = 13;
        players[3].pieces[i].approach_counter = 0;
        players[3].pieces[i].six_counter = 0;
    }
}

void move_piece(struct Player *player, int piece_index, int steps) {
    // Move the specified piece by a given number of steps
    player->pieces[piece_index].current_position += steps;
    if (player->pieces[piece_index].current_position > 51) {
        player->pieces[piece_index].current_position = player->pieces[piece_index].current_position % 52;
    }
}

void print_game_state(struct Player players[]) {
    for (int i = 0; i < 4; i++) {
        printf("Player %c:\n", players[i].playerid);
        for (int j = 0; j < 4; j++) {
            printf("  Piece %d - Current Position: %d, Starting Position: %d\n", 
                   players[i].pieces[j].pieceid, 
                   players[i].pieces[j].current_position, 
                   players[i].pieces[j].starting_position);
        }
    }
}

int roll_dice() {
    // Return a random number between 1 and 6
    return (rand() % 6) + 1;
}

