#ifndef TYPES_H
#define TYPES_H

#define NUM_PLAYERS 4
#define NUM_PIECES 4
#define BOARD_SIZE 52

struct Player {
    char name;  // Player's name ('R', 'G', 'B', 'Y')
    int pieces[NUM_PIECES];  // Positions of the 4 pieces
};

// Function prototypes
void initializePlayers(struct Player players[NUM_PLAYERS]);
void displayPositions(struct Player players[NUM_PLAYERS]);

#endif // TYPES_H

