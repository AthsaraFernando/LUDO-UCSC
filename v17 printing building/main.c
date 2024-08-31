#include "types.h"
#include <stdio.h>

int main() {
    int game_on = 1;
    int round = 0;
    struct Player players[4];
    int player_order[4];
    int initial_rolls[4];

    // Initialize random number generator
    initialize_random();

    // Initialize players and pieces
    initialize_players(players);
    printf("\nThe Red player has four (04) pieces named R1, R2, R3, and R4\n");
    printf("The Green player has four (04) pieces named G1, G2, G3, and G4\n");
    printf("The Yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
    printf("The Blue player has four (04) pieces named B1, B2, B3, and B4\n\n");

    // Each player rolls the dice to determine the starting player
    for (int i = 0; i < 4; i++) {
        initial_rolls[i] = roll_dice();
        printf("%c rolls %d\n", players[i].playerid, initial_rolls[i]);
    }

    // Determine the starting player based on the highest roll
    int starting_player = determine_starting_player(initial_rolls);
    printf("\n%c Player has the highest roll and will begin the game.\n", players[starting_player].playerid);

    // Determine the player order based on the starting player
    determine_player_order(starting_player, player_order);

    // Display the player order
    printf("\nThe order of a single round is: ");
    for (int i = 0; i < 4; i++) {
        printf("%c ", players[player_order[i]].playerid);
    }
    printf("\n");

    // main gameplay loop until 3 players win
    while(game_on) { 
	int piece_index = -1;

        printf("\nRound %d\n", round + 1);
        printf("-----------------------------------------------------\n");
        for (int i = 0; i < 4; i++) {
            int current_player_index = player_order[i];
	    for(int j=0; j<2; j++){
            	// Roll dice for the current player
            	int dice_roll = roll_dice();
            	printf("Player %c rolled a %d\n", players[current_player_index].playerid, dice_roll);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//piece_index = round % 4;		
	piece_index = 0;	

	/*
	// Behaviour of Green Player
	if(current_player_index == 1){
		//piece_index = round % 4;		
		piece_index = 0;	
		printf("Piece Index = %d\n", piece_index);
	
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
		}	
	
	}
	


	
	
	// Behaviour of Red Player
	else if(current_player_index == 0){
		//piece_index = round % 4;	
		piece_index = 0;	
		printf("Piece Index = %d\n", piece_index);
	}	

	// Behaviour of Yellow Player
	else if(current_player_index == 2){
		//piece_index = round % 4;
		piece_index = 0;	
		printf("Piece Index = %d\n", piece_index);
	}	

	// Behaviour of Blue Player
	else if(current_player_index == 3){
		//piece_index = round % 4;
		piece_index = 0;	
		printf("Piece Index = %d\n", piece_index);
	}
	*/
	
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
	game_on = check_game_on(players);
	printf("\n");
	}

	//game_on = check_game_on(players);
	//printf("Game on %d = \n",game_on);
    }

    return 0;
}


