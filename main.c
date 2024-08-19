#include <stdio.h>
#include "types.h"

int main() {
    struct Player players[4];

    // Initialize players and pieces
    initialize_players(players);

    // Print initial game state
    printf("Initial Game State:\n");
    print_game_state(players);

    // Example of moving a piece
    printf("\nMoving Player R's piece 0 by 5 steps...\n");
    move_piece(&players[0], 0, 5);

    // Print updated game state
    printf("\nUpdated Game State:\n");
    print_game_state(players);

    // Example of moving a piece
    printf("\nMoving Player G's piece 0 by 5 steps...\n");
    move_piece(&players[1], 0, 7);

    // Print updated game state
    printf("\nUpdated Game State:\n");
    print_game_state(players);



    // Example of moving a piece
    printf("\nMoving Player R's piece 0 by 5 steps...\n");
    move_piece(&players[0], 0, 5);

    // Print updated game state
    printf("\nUpdated Game State:\n");
    print_game_state(players);




    return 0;
}

