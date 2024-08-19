#include <stdio.h>
#include "types.h"

int main() {
    struct Player players[TOTAL_PLAYERS];

    // Initialize players and their pieces
    initPlayers(players);

    // Move some pieces for demonstration
    movePiece(&players[0], 0, 5);  // Move R1 by 5 steps
    movePiece(&players[1], 1, 3);  // Move G2 by 3 steps
    movePiece(&players[2], 2, 7);  // Move B3 by 7 steps

    // Print the current board status
    printBoard(players);

    return 0;
}

