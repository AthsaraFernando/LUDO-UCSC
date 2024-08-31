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
    for (int round = 0; round < 75; round++) { // Example: 5 rounds of play
	int piece_index = -1;


        printf("\nRound %d\n", round + 1);
        for (int i = 0; i < 4; i++) {
            int current_player_index = player_order[i];
	    for(int j=0; j<2; j++){
           	 printf("\nPlayer %c's turn.\n", players[current_player_index].playerid);
            
            	// Roll dice for the current player
            	int dice_roll = roll_dice();
            	printf("Player %c rolled a %d\n", players[current_player_index].playerid, dice_roll);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Green Player Behaviour
	if(current_player_index == 1){
		for(int i=0; i<4 ; i++){
			land_on_same_cell(&players[current_player_index], i, dice_roll, players);
			if(players[1].pieces[i].finished != 1 && players[1].pieces[i].land_same_color_cell == 0){
				if(players[1].pieces[i].in_base == 1){
					if( dice_roll == 6){
						piece_index = i;
						// Resetting the resutls of land_on_same_cell function
						players[1].pieces[i].land_same_color_cell = 0;	
						players[1].pieces[i].capture_ability = 0;	
						for(int k = 0; k < 4; k++) {
							for(int j = 0; j < 4; j++) {
								players[k].pieces[j].capturable = 0; 
							}
						}
						break;
					}	
				}
				else{
					if(players[1].pieces[i].capture_ability == 0){
						if(players[1].pieces[i].pieceid == round % 4){
							piece_index = round % 4;
							break;
						}
						else{ 
							piece_index = players[1].pieces[i].pieceid;
							// Resetting the resutls of land_on_same_cell function
							players[1].pieces[i].land_same_color_cell = 0;	
							players[1].pieces[i].capture_ability = 0;	
							for(int k = 0; k < 4; k++) {
								for(int j = 0; j < 4; j++) {
									players[k].pieces[j].capturable = 0; 
								}
							}
							break;
						}
					}
				}
			}
			// Resetting the resutls of land_on_same_cell function
			players[1].pieces[i].land_same_color_cell = 0;	
			players[1].pieces[i].capture_ability = 0;	
			for(int k = 0; k < 4; k++) {
				for(int j = 0; j < 4; j++) {
					players[k].pieces[j].capturable = 0; 
				}
			}
		}

		if(piece_index == -1){
			for(int i=0; i<4 ; i++){
				if(players[1].pieces[i].finished != 1){
					if(players[1].pieces[i].in_base == 0){
						if(players[1].pieces[i].capture_ability == 1){
							if(players[1].pieces[i].pieceid == round % 4){
								piece_index = round % 4;
							}
							else{ 
								piece_index = players[1].pieces[i].pieceid;
							}
						}
					}
				}			// Resetting the resutls of land_on_same_cell function
			players[1].pieces[i].land_same_color_cell = 0;	
			players[1].pieces[i].capture_ability = 0;	
			for(int k = 0; k < 4; k++) {
				for(int j = 0; j < 4; j++) {
					players[k].pieces[j].capturable = 0; 
				}
			}
			}
		}	
	}
			
	else if(current_player_index == 0){
		piece_index = 0;
		printf("Piece Index = %d\n", piece_index);
	}	
	else if(current_player_index == 2){
		piece_index = 0;
		printf("Piece Index = %d\n", piece_index);
	}	
	else if(current_player_index == 3){
		piece_index = round % 4;
		printf("Piece Index = %d\n", piece_index);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    	
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


