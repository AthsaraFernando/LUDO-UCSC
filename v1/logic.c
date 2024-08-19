#include <stdio.h>
#include <string.h>
#include "types.h"

// Initialize the players and their pieces
void initPlayers(struct Player players[TOTAL_PLAYERS]) {
    char playerIDs[] = {'R', 'G', 'B', 'Y'};
    
    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        players[i].playerID = playerIDs[i];
        
        // Assign piece IDs correctly (e.g., 'R1', 'R2', ..., 'Y4')
        for (int j = 0; j < MAX_PIECES; j++) {
            players[i].pieces[j].id[0] = playerIDs[i]; // Set 'R', 'G', etc.
            players[i].pieces[j].id[1] = '1' + j; // Set '1', '2', ..., '4'
            players[i].pieces[j].id[2] = '\0'; // Null terminate the string
            
            players[i].pieces[j].position = 0; // Initialize position to 0
        }
    }
}

// Move a specific piece by a certain number of steps
void movePiece(struct Player* player, int pieceIndex, int steps) {
    if (pieceIndex >= 0 && pieceIndex < MAX_PIECES) {
        player->pieces[pieceIndex].position = (player->pieces[pieceIndex].position + steps) % (MAX_POSITION + 1);
    }
}

// Print the board status
void printBoard(struct Player players[TOTAL_PLAYERS]) {
    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        printf("Player %c:\n", players[i].playerID);
        for (int j = 0; j < MAX_PIECES; j++) {
            printf("  Piece %s: Position %d\n", players[i].pieces[j].id, players[i].pieces[j].position);
        }
        printf("\n");
    }
}

