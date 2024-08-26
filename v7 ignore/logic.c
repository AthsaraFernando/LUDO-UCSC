#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Seed the random number generator
void initialize_random() {
    srand(time(NULL)); // Seed with current time
}

// Initialize players and their pieces
void initialize_players(struct Player players[]) {
    // Initialize Player R (Red)
    players[0].playerid = 'R';
    for (int i = 0; i < 4; i++) {
        players[0].pieces[i].pieceid = i;
        players[0].pieces[i].current_position = 28;
        players[0].pieces[i].starting_position = 28;
        players[0].pieces[i].no_captured = 0;
        players[0].pieces[i].clockwise = 1;
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
        players[1].pieces[i].clockwise = 1;
        players[1].pieces[i].approach_position = 39;
        players[1].pieces[i].approach_counter = 0;
        players[1].pieces[i].six_counter = 0;
    }

    // Initialize Player B (Blue)
    players[2].playerid = 'B';
    for (int i = 0; i < 4; i++) {
        players[2].pieces[i].pieceid = i;
        players[2].pieces[i].current_position = 15;
        players[2].pieces[i].starting_position = 15;
        players[2].pieces[i].no_captured = 0;
        players[2].pieces[i].clockwise = 1;
        players[2].pieces[i].approach_position = 13;
        players[2].pieces[i].approach_counter = 0;
        players[2].pieces[i].six_counter = 0;
    }

    // Initialize Player Y (Yellow)
    players[3].playerid = 'Y';
    for (int i = 0; i < 4; i++) {
        players[3].pieces[i].pieceid = i;
        players[3].pieces[i].current_position = 2;
        players[3].pieces[i].starting_position = 2;
        players[3].pieces[i].no_captured = 0;
        players[3].pieces[i].clockwise = 1;
        players[3].pieces[i].approach_position = 0;
        players[3].pieces[i].approach_counter = 0;
        players[3].pieces[i].six_counter = 0;
    }
}

// Function to move a piece forward
void move_piece_forward(struct Player *player, int piece_index, int steps) {
    struct Piece *piece = &player->pieces[piece_index];

    // Check if the piece is in the special zone
    if (piece->current_position >= 95 && piece->current_position <= 100) return;
    if (piece->current_position >= 195 && piece->current_position <= 200) return;
    if (piece->current_position >= 295 && piece->current_position <= 300) return;
    if (piece->current_position >= 395 && piece->current_position <= 400) return;

    // Move the piece forward by the number of steps
    piece->current_position += steps;

    // Handle wrapping around the board
    if (piece->current_position > 51) {
        piece->current_position = piece->current_position % 52;
    }

    // Check if the piece has passed the approach cell position
    if (piece->current_position >= piece->approach_position) {
        switch (player->playerid) {
            case 'R':
                if (piece->current_position >= 26) {
                    piece->current_position = 95 + (piece->current_position - 26);
                }
                break;
            case 'G':
                if (piece->current_position >= 39) {
                    piece->current_position = 195 + (piece->current_position - 39);
                }
                break;
            case 'Y':
                if (piece->current_position >= 0) {
                    piece->current_position = 295 + (piece->current_position - 0);
                }
                break;
            case 'B':
                if (piece->current_position >= 13) {
                    piece->current_position = 395 + (piece->current_position - 13);
                }
                break;
        }
    }
}

// Function to print the current game state
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

// Function to roll a dice
int roll_dice() {
    return (rand() % 6) + 1; // Return a random number between 1 and 6
}

// Function to determine player order based on initial rolls
void determine_player_order(struct Player players[], int order[]) {
    int rolls[4];
    int highest_roll = -1;
    int highest_player = -1;

    // Each player rolls the dice to determine the order
    for (int i = 0; i < 4; i++) {
        rolls[i] = roll_dice();
        printf("Player %c rolled a %d\n", players[i].playerid, rolls[i]);
        if (rolls[i] > highest_roll) {
            highest_roll = rolls[i];
            highest_player = i;
        }
    }

    // Set the order based on the highest roll and player IDs
    order[0] = highest_player;
    order[1] = (highest_player + 1) % 4;
    order[2] = (highest_player + 2) % 4;
    order[3] = (highest_player + 3) % 4;
}

