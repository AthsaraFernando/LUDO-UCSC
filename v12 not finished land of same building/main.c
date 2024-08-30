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
    for (int round = 0; round < 25; round++) { // Example: 5 rounds of play
	int piece_index = 0;
        printf("\nRound %d\n", round + 1);
        for (int i = 0; i < 4; i++) {
            int current_player_index = player_order[i];
	    for(int j=0; j<2; j++){
           	 printf("\nPlayer %c's turn.\n", players[current_player_index].playerid);
            
	    
	    
            	// Roll dice for the current player
            	int dice_roll = roll_dice();
            	printf("Player %c rolled a %d\n", players[current_player_index].playerid, dice_roll);
	
	    	//main play start	
	    	play(&players[current_player_index], piece_index, dice_roll, players);
            	
            	// Print updated game state
		print_game_state(players);
	
		//stops repeating if six counter is not 0-1
		if(players[current_player_index].pieces[piece_index].six_counter == 0 || players[current_player_index].pieces[piece_index].six_counter > 2){
	    		break;	
	    	}

	    
            }
	    players[current_player_index].pieces[piece_index].six_counter = 0;
	}
    }

    return 0;
}


