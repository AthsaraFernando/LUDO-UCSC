#ifndef TYPES_H
#define TYPES_H

// Define the Piece struct
struct Piece {
    int pieceid;               // 0, 1, 2, 3 (ID of the piece)
    int current_position;      // 0-51 (Position on the board)
    int base_position;         // initial base position (just a negative value to deviate)
    int traveled_cells;        // number of traveled cells 
    int starting_position;     // Starting positions: Y=2, B=15, R=28, G=41
    int home_start;    	       // Starting positions: Y=2, B=15, R=28, G=41
    int no_captured;           // Number of pieces captured by this piece, initialized to 0
    int clockwise;             // Moving direction (1 heads for clockwise, 0 is tail for counterclockwise), not initialized yet
    int approach_position;     // Approach cell position: R=26, G=39, Y=0, B=13
    int six_counter;           // Counter for the number of times a piece has rolled a 6, initialized to 0
    int in_base;               // 1 if still in base, 0 if out of the base
    int land_same_color_cell;  //to check if the piece will land on a same color piece cell.
    int capturable;            // Means vulnarable to be captured by another player
    int capture_ability;       // Does have the ability to capture another player's piece 
    int is_rolling_piece;      // identifier to show the currently moving piece
    //int energized;	       // energized mystery affect of Bhawana is stored here
    //int sick;		       // sick mystery affect of Bhawana is stored here
    //int kotuwa_paused;       // mystery affect of kotuwa is stored here
    int finished;	       // check if the piece has arived to the home or not.
};

// Define the Player struct, which contains an array of 4 Piece structs
struct Player {
    char playerid;             // 'R', 'G', 'Y', 'B' (ID of the player)
    int player_rank ;
    struct Piece pieces[4];    // Array of 4 pieces for each player
};

// Function prototypes
void initialize_players(struct Player players[]);
void take_out_base(struct Player *player, int piece_index, int steps);
void move_piece_forward(struct Player *player, int piece_index, int steps);
void move_piece_backward(struct Player *player, int piece_index, int steps);
void play(struct Player *player, int piece_index, int steps, struct Player players[]);
void land_on_same_cell(struct Player *player, int piece_index, int steps, struct Player players[]);
void print_game_state(struct Player players[]);
int check_game_on(struct Player players[]);
int roll_dice(); // Function prototype for rolling a dice
void initialize_random(); // Function prototype for initializing random number generator
int determine_starting_player(int initial_rolls[]);
void determine_player_order(int starting_player, int player_order[]);
void run_game();
void mystery_cell_generate(struct Player players[]);
void activate_mystery(struct Player *player, int piece_index, struct Player players[]);

#endif


