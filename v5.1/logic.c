#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_random() {
    srand(time(NULL));
}

void initialize_players(struct Player players[]) {
    players[0].playerid = 'R';
    for (int i = 0; i < 4; i++) {
        players[0].pieces[i].pieceid = i;
        players[0].pieces[i].current_position = 28;
        players[0].pieces[i].starting_position = 28;
        players[0].pieces[i].no_captured = 0;
        players[0].pieces[i].approach_position = 26;
        players[0].pieces[i].approach_counter = 0;
        players[0].pieces[i].six_counter = 0;
    }

    players[1].playerid = 'G';
    for (int i = 0; i < 4; i++) {
        players[1].pieces[i].pieceid = i;
        players[1].pieces[i].current_position = 41;
        players[1].pieces[i].starting_position = 41;
        players[1].pieces[i].no_captured = 0;
        players[1].pieces[i].approach_position = 39;
        players[1].pieces[i].approach_counter = 0;
        players[1].pieces[i].six_counter = 0;
    }

    players[2].playerid = 'Y';
    for (int i = 0; i < 4; i++) {
        players[2].pieces[i].pieceid = i;
        players[2].pieces[i].current_position = 2;
        players[2].pieces[i].starting_position = 2;
        players[2].pieces[i].no_captured = 0;
        players[2].pieces[i].approach_position = 0;
        players[2].pieces[i].approach_counter = 0;
        players[2].pieces[i].six_counter = 0;
    }

    players[3].playerid = 'B';
    for (int i = 0; i < 4; i++) {
        players[3].pieces[i].pieceid = i;
        players[3].pieces[i].current_position = 15;
        players[3].pieces[i].starting_position = 15;
        players[3].pieces[i].no_captured = 0;
        players[3].pieces[i].approach_position = 13;
        players[3].pieces[i].approach_counter = 0;
        players[3].pieces[i].six_counter = 0;
    }
}

void move_piece(struct Player *player, int piece_index, int steps) {
    player->pieces[piece_index].current_position += steps;
    if (player->pieces[piece_index].current_position > 51) {
        player->pieces[piece_index].current_position %= 52;
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
    return (rand() % 6) + 1;
}

int determine_starting_player(int initial_rolls[]) {
    int highest_roll = initial_rolls[0];
    int starting_player = 0;

    for (int i = 1; i < 4; i++) {
        if (initial_rolls[i] > highest_roll) {
            highest_roll = initial_rolls[i];
            starting_player = i;
        }
    }
    return starting_player;
}

void determine_player_order(int starting_player, int player_order[]) {
    int base_order[4] = {0, 1, 2, 3};  // R=0, G=1, Y=2, B=3
    int order_start = base_order[starting_player];
    
    for (int i = 0; i < 4; i++) {
        player_order[i] = base_order[(order_start + i) % 4];
    }
}

