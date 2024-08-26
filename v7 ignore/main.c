#include "types.h"
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void initialize_random();
void initialize_players(struct Player players[]);
void move_piece_forward(struct Player *player, int piece_index, int steps);
void print_game_state(struct Player players[]);
int roll_dice();
void determine_player_order(struct Player players[], int order[]);

int main() {
    struct Player players[4];
    int order[4];

    // Initialize random number generator
    initialize_random();

    // Initialize players and their pieces
    initialize_players(players);

    // Determine player order based on initial rolls
    determine_player_order(players, order);

    // Print the initial game state
    print_game_state(players);

    // Simulate a few turns of the game
    for (int turn = 0; turn < 10; turn++) {
        printf("\nTurn %d:\n", turn + 1);
        for (int i = 0; i < 4; i++) {
            int player_index = order[i];
            printf("Player %c's turn:\n", players[player_index].playerid);
            for (int j = 0; j < 4; j++) {
                int steps = roll_dice(); // Roll dice for each piece
                printf("  Moving piece %d of Player %c by %d steps.\n",
                       players[player_index].pieces[j].pieceid,
                       players[player_index].playerid,
                       steps);
                move_piece_forward(&players[player_index], j, steps);
            }
            print_game_state(players);
        }
    }

    return 0;
}

