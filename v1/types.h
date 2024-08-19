#ifndef TYPES_H
#define TYPES_H

#define MAX_PIECES 4
#define MAX_POSITION 51
#define TOTAL_PLAYERS 4  // Fixed number of players

struct Player {
    char playerID;   // Player identifier ('R', 'G', 'B', 'Y')
    struct Piece {   // Embedded Piece structure within Player
        char id[3];  // Piece identifier (e.g., 'R1', 'G2', etc.)
        int position;  // Position on the board (0-51)
    } pieces[MAX_PIECES];  // Array of player's pieces
};

void initPlayers(struct Player players[TOTAL_PLAYERS]);
void movePiece(struct Player* player, int pieceIndex, int steps);
void printBoard(struct Player players[TOTAL_PLAYERS]);

#endif

