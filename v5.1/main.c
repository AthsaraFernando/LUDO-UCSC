#include "types.h"
#include <stdio.h>

int main() {
    struct Player players[4];
    int player_order[4];
    int initial_rolls[4];

    // Initialize random number generator
    initialize_random();

    // Initialize players and pieces
    initialize_players(players);

    // Each player rolls the dice to determine the starting player
    printf("Rolling dice to determine the starting player...\n");
    for (int i = 0; i < 4; i++) {
        initial_rolls[i] = roll_dice();
        printf("Player %c rolled a %d\n", players[i].playerid, initial_rolls[i]);
    }

    // Determine the starting player based on the highest roll
    int starting_player = determine_starting_player(initial_rolls);
    printf("\nPlayer %c will start the game.\n", players[starting_player].playerid);

    // Determine the player order based on the starting player
    determine_player_order(starting_player, player_order);

    // Display the player order
    printf("\nPlayer order is: ");
    for (int i = 0; i < 4; i++) {
        printf("%c ", players[player_order[i]].playerid);
    }
    printf("\n");

    // Example gameplay loop for each player in order
    for (int round = 0; round < 5; round++) { // Example: 5 rounds of play
        printf("\nRound %d\n", round + 1);
        for (int i = 0; i < 4; i++) {
            int current_player_index = player_order[i];
            printf("Player %c's turn.\n", players[current_player_index].playerid);
            
            // Roll dice for the current player
            int dice_roll = roll_dice();
            printf("Player %c rolled a %d\n", players[current_player_index].playerid, dice_roll);

            // Move the player's piece 0 by the dice roll value
            printf("Moving Player %c's piece 0 by %d steps...\n", players[current_player_index].playerid, dice_roll);
            move_piece(&players[current_player_index], 0, dice_roll);

            // Print updated game state
            print_game_state(players);
        }
    }

    return 0;
}

