#include <stdio.h>
#include "types.h"

int main() {
    struct Player players[4];

    // Initialize players and pieces
    initialize_players(players);

    // Print initial game state
    printf("Initial Game State:\n");
    print_game_state(players);

    // Example of rolling a dice
    printf("\nRolling dice for Player R...\n");
    int dice_roll = roll_dice();
    printf("Player R rolled a %d\n", dice_roll);

    // Example of moving a piece
    printf("\nMoving Player R's piece 0 by %d steps...\n", dice_roll);
    move_piece(&players[0], 0, dice_roll);

    // Print updated game state
    printf("\nUpdated Game State:\n");
    print_game_state(players);

    return 0;
}

