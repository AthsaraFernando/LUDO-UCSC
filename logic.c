#include <stdio.h>
#include "types.h"

void initializePlayers(struct Player players[NUM_PLAYERS]) {
    // Initialize players with their names and starting positions
    players[0].name = 'Y';
    players[1].name = 'B';
    players[2].name = 'R';
    players[3].name = 'G';

    // Set initial positions for each player's pieces
    for (int i = 0; i < NUM_PIECES; i++) {
        players[0].pieces[i] = 2;   // Yellow pieces start at position 2
        players[1].pieces[i] = 15;  // Blue pieces start at position 15
        players[2].pieces[i] = 28;  // Red pieces start at position 28
        players[3].pieces[i] = 41;  // Green pieces start at position 41
    }
}

void displayPositions(struct Player players[NUM_PLAYERS]) {
    // Display each player's pieces and their positions
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %c's pieces positions:\n", players[i].name);
        for (int j = 0; j < NUM_PIECES; j++) {
            printf("  %c%d is at position %d\n", players[i].name, j + 1, players[i].pieces[j]);
        }
    }
}

