#ifndef TYPES_H
#define TYPES_H

// Define the Piece struct
struct Piece {
    int pieceid;               // 0, 1, 2, 3 (ID of the piece)
    int current_position;      // 0-51 (Position on the board)
    int starting_position;     // Starting positions: Y=2, B=15, R=28, G=41
    int no_captured;           // Number of pieces captured by this piece, initialized to 0
    int clockwise;             // Moving direction (1 for clockwise, 0 for counterclockwise), not initialized yet
    int approach_position;     // Approach cell position: R=26, G=39, Y=0, B=13
    int approach_counter;      // Approach cell counter, initialized to 0
    int six_counter;           // Counter for the number of times a piece has rolled a 6, initialized to 0
};

// Define the Player struct, which contains an array of 4 Piece structs
struct Player {
    char playerid;             // 'R', 'G', 'Y', 'B' (ID of the player)
    struct Piece pieces[4];    // Array of 4 pieces for each player
};

// Function prototypes
void initialize_players(struct Player players[]);
void move_piece_forward(struct Player *player, int piece_index, int steps);
void print_game_state(struct Player players[]);
int roll_dice(); // Function prototype for rolling a dice
void initialize_random(); // Function prototype for initializing random number generator
int determine_starting_player(int initial_rolls[]);
void determine_player_order(int starting_player, int player_order[]);

#endif

