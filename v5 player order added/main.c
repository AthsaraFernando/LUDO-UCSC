#include <stdio.h>
#include "types.h"

int determine_starting_player(struct Player players[], int initial_rolls[]);

int main() {
    struct Player players[4];
    int initial_rolls[4];  // To store the initial rolls of all players
    int player_order[4];   // To store the order of players based on the initial rolls

    // Seed the random number generator
    initialize_random();

    // Initialize players and pieces
    initialize_players(players);

    // Each player rolls the dice to determine the starting player
    printf("Determining player order...\n");
    for (int i = 0; i < 4; i++) {
        initial_rolls[i] = roll_dice();
        printf("Player %c rolled a %d\n", players[i].playerid, initial_rolls[i]);
    }

    // Determine the player who will start the game
    int starting_player = determine_starting_player(players, initial_rolls);

    // Fill the player_order array based on the starting player and your custom order R->G->Y->B
    for (int i = 0; i < 4; i++) {
        player_order[i] = (starting_player + i) % 4;
    }

    // Adjust the order to match the sequence R->G->Y->B relative to the starting player
    int adjusted_order[4];
    for (int i = 0; i < 4; i++) {
        adjusted_order[i] = (starting_player + i) % 4;
        if (adjusted_order[i] == 0) adjusted_order[i] = 0; // R
        else if (adjusted_order[i] == 1) adjusted_order[i] = 1; // G
        else if (adjusted_order[i] == 2) adjusted_order[i] = 2; // Y
        else if (adjusted_order[i] == 3) adjusted_order[i] = 3; // B
    }

    // Print the determined player order
    printf("Starting player is Player %c\n", players[starting_player].playerid);
    printf("Player order: ");
    for (int i = 0; i < 4; i++) {
        printf("%c ", players[adjusted_order[i]].playerid);
    }
    printf("\n");

    // Simulate a few rounds of the game with the determined player order
    for (int round = 0; round < 5; round++) {  // Example: 5 rounds
        printf("\nRound %d\n", round + 1);
        for (int i = 0; i < 4; i++) {
            int current_player_index = adjusted_order[i];
            printf("\nRolling dice for Player %c...\n", players[current_player_index].playerid);
            int dice_roll = roll_dice();
            printf("Player %c rolled a %d\n", players[current_player_index].playerid, dice_roll);

            // Move the current player's first piece by the dice roll value
            printf("Moving Player %c's piece 0 by %d steps...\n", players[current_player_index].playerid, dice_roll);
            move_piece(&players[current_player_index], 0, dice_roll);

            // Print updated game state after each player's turn
            print_game_state(players);
        }
    }

    return 0;
}

// Function to determine the starting player based on the initial rolls
int determine_starting_player(struct Player players[], int initial_rolls[]) {
    int highest_roll = initial_rolls[0];
    int starting_player = 0;

    // Find the player with the highest roll
    for (int i = 1; i < 4; i++) {
        if (initial_rolls[i] > highest_roll) {
            highest_roll = initial_rolls[i];
            starting_player = i;
        }
    }

    return starting_player;
}

