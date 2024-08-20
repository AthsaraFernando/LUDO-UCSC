#include <stdio.h>
#include "types.h"

int main() {
    struct Player players[4];

    // Seed the random number generator
    initialize_random();

    // Initialize players and pieces
    initialize_players(players);

    // Print initial game state
    printf("Initial Game State:\n");
    print_game_state(players);

    // Simulate multiple rolls for Player R
    for (int i = 0; i < 5; i++) { // Example: 5 rolls
        printf("\nRolling dice for Player R...\n");
        int dice_roll_R = roll_dice();
        printf("Player R rolled a %d\n", dice_roll_R);

        // Move Player R's piece 0 by the dice roll value
        printf("Moving Player R's piece 0 by %d steps...\n", dice_roll_R);
        move_piece(&players[0], 0, dice_roll_R);

        // Print updated game state after each roll
        printf("\nUpdated Game State after roll %d:\n", i + 1);
        print_game_state(players);
    }

    return 0;
}

