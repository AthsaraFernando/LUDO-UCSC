#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_players(struct Player players[]) {
    // Initialize Player R (Red)
    players[0].playerid = 'R';
    for (int i = 0; i < 4; i++) {
        players[0].pieces[i].pieceid = i;
        players[0].pieces[i].current_position = 28;
        players[0].pieces[i].starting_position = 28;
    }

    // Initialize Player G (Green)
    players[1].playerid = 'G';
    for (int i = 0; i < 4; i++) {
        players[1].pieces[i].pieceid = i;
        players[1].pieces[i].current_position = 41;
        players[1].pieces[i].starting_position = 41;
    }

    // Initialize Player B (Blue)
    players[2].playerid = 'B';
    for (int i = 0; i < 4; i++) {
        players[2].pieces[i].pieceid = i;
        players[2].pieces[i].current_position = 15;
        players[2].pieces[i].starting_position = 15;
    }

    // Initialize Player Y (Yellow)
    players[3].playerid = 'Y';
    for (int i = 0; i < 4; i++) {
        players[3].pieces[i].pieceid = i;
        players[3].pieces[i].current_position = 2;
        players[3].pieces[i].starting_position = 2;
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
            printf("  Piece %d - Current Position: %d\n", 
                   players[i].pieces[j].pieceid, 
                   players[i].pieces[j].current_position);
        }
    }
}

int roll_dice() {
    // Seed the random number generator
    srand(time(NULL));

    // Return a random number between 1 and 6
    return (rand() % 6) + 1;
}

