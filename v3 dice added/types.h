#ifndef TYPES_H
#define TYPES_H

// Define the Piece struct
struct Piece {
    int pieceid;           // 0, 1, 2, 3 (ID of the piece)
    int current_position;  // 0-51 (Position on the board)
    int starting_position; // Starting positions: Y=2, B=15, R=28, G=41
};

// Define the Player struct, which contains an array of 4 Piece structs
struct Player {
    char playerid;         // 'R', 'G', 'B', 'Y' (ID of the player)
    struct Piece pieces[4]; // Array of 4 pieces for each player
};

// Function prototypes
void initialize_players(struct Player players[]);
void move_piece(struct Player *player, int piece_index, int steps);
void print_game_state(struct Player players[]);
int roll_dice(); // Function prototype for rolling a dice

#endif

