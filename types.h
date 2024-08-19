#ifndef TYPES_H
#define TYPES_H

// Struct to represent each piece of a player
struct Piece {
    int pieceid;           // 0, 1, 2, 3
    int current_position;  // 0-51
    int starting_position; // Starting positions: 2 (Y), 15 (B), 28 (R), 41 (G)
};

// Struct to represent each player
struct Player {
    char playerid;         // 'R', 'G', 'B', 'Y'
    struct Piece pieces[4]; // Each player has 4 pieces
};

// Function prototypes
void initialize_players(struct Player players[]);
void move_piece(struct Player *player, int piece_index, int steps);
void print_game_state(struct Player players[]);

#endif

