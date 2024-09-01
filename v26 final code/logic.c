#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
		 
// Seed the random number generator once at the start of the program
void initialize_random() {
    srand(time(NULL)); // Seed with current time
}

// Initialize the players and their pieces
void initialize_players(struct Player players[]) {
	char player_ids[4] = {'R', 'G', 'Y', 'B'};
    	int starting_positions[4] = {28, 41, 2, 15};
    	int home_starts[4] = {95, 195, 295, 395};
    	int approach_positions[4] = {26, 39, 0, 13};
    	int base_positions[4] = {-1, -2, -3, -4};
    
    	for (int j = 0; j < 4; j++) {
        	players[j].playerid = player_ids[j];
        	for (int i = 0; i < 4; i++) {
            		players[j].pieces[i].pieceid = i;
            		players[j].pieces[i].current_position = base_positions[j];
            		players[j].pieces[i].base_position = base_positions[j];
            		players[j].pieces[i].traveled_cells = 0;
            		players[j].pieces[i].starting_position = starting_positions[j];
            		players[j].pieces[i].home_start = home_starts[j];
            		players[j].pieces[i].no_captured = 0;
            		players[j].pieces[i].approach_position = approach_positions[j];
            		players[j].pieces[i].six_counter = 0;
            		players[j].pieces[i].clockwise = 1;
            		players[j].pieces[i].in_base = 1;
            		players[j].pieces[i].land_same_color_cell = 0;
            		players[j].pieces[i].capturable = 0;
            		players[j].pieces[i].capture_ability = 0;
            		players[j].pieces[i].is_rolling_piece = 0;
            		//players[j].pieces[i].energized = 0;
            		//players[j].pieces[i].sick = 0;
            		//players[j].pieces[i].kotuwa_paused = 0;
            		players[j].pieces[i].finished = 0;
        	}
    	}
}

// function to take the pieces out from the base
void take_out_base(struct Player *player, int piece_index, int steps) {
	if(player->pieces[piece_index].in_base == 1 && steps==6){
		player->pieces[piece_index].in_base = 0;
		player->pieces[piece_index].current_position = player->pieces[piece_index].starting_position;
	}
}

// Move the specified piece forward by a given number of steps
void move_piece_forward(struct Player *player, int piece_index, int steps) {
	if(player->pieces[piece_index].in_base == 0){
		player->pieces[piece_index].traveled_cells += steps;	
		if(player->pieces[piece_index].traveled_cells < 51){		
			player->pieces[piece_index].current_position += steps;
    			if (player->pieces[piece_index].current_position > 51) {
        			player->pieces[piece_index].current_position %= 52; // Wrap around the board
    			}
		}
		else{
			if(player->pieces[piece_index].traveled_cells <= 56 ){
				player->pieces[piece_index].current_position = player->pieces[piece_index].traveled_cells - 51 + player->pieces[piece_index].home_start;
			}
			else{
				player->pieces[piece_index].traveled_cells -= steps;	
	
			}
		}
	}
	
	if(player->pieces[piece_index].traveled_cells == 56){    // player has reached the final home  
		player->pieces[piece_index].finished = 1;
		
	}
}

// Move the specified piece backward by a given number of steps
void move_piece_backward(struct Player *player, int piece_index, int steps) {
	if(player->pieces[piece_index].in_base == 0){
		player->pieces[piece_index].traveled_cells += steps;	
		if(player->pieces[piece_index].traveled_cells < 55){		
			player->pieces[piece_index].current_position -= steps;
    			if (player->pieces[piece_index].current_position < 0) {
        			player->pieces[piece_index].current_position += 52; // Wrap around the board
    			}
		}
		else{
			if(player->pieces[piece_index].traveled_cells <= 60 ){
				player->pieces[piece_index].current_position = player->pieces[piece_index].traveled_cells - 55 + player->pieces[piece_index].home_start;
			}
			else{
				player->pieces[piece_index].traveled_cells -= steps;	
	
			}
		}
	}
	
	if(player->pieces[piece_index].traveled_cells == 60){    // player has reached the final home  
		player->pieces[piece_index].finished = 1;
		
	}
}

// check if a piece lands on a cell where there is another piece (same or different player)
void land_on_same_cell(struct Player *player, int piece_index, int steps, struct Player players[]) {
	if(player->pieces[piece_index].in_base == 0 && player->pieces[piece_index].current_position <52){
		int destination = (player->pieces[piece_index].current_position + steps) % 52;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				if (players[i].pieces[j].current_position == destination ) {
					if(players[i].playerid == player->playerid && j == piece_index){
						player->pieces[piece_index].land_same_color_cell = 1;	
                				printf("Player %c's piece %d lands on the same cell as Player %c's piece %d \n",
								player->playerid, piece_index, players[i].playerid, j);
					}
					else{
						players[i].pieces[j].capturable = 1; 
						player->pieces[piece_index].capture_ability = 1;	
					}
				}	
        		}	
		}
    	}
	else if(player->pieces[piece_index].in_base == 1 && steps == 6){
		int destination = player->pieces[piece_index].starting_position;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				if (players[i].pieces[j].current_position == destination ) {
					if(players[i].playerid == player->playerid && j == piece_index){
						player->pieces[piece_index].land_same_color_cell = 1;	
                				printf("Player %c's piece %d lands on the same cell as Player %c's piece %d \n",
						player->playerid, piece_index, players[i].playerid, j);
					}
					else{
						players[i].pieces[j].capturable = 1; 
						player->pieces[piece_index].capture_ability = 1;	
                			}
				}	
        		}
		}
	}
}

// function of capturing pieces
void capture_piece(struct Player *player, int piece_index, int steps, struct Player players[]) {
	player->pieces[piece_index].no_captured +=1; // increase the captured pieces count
	int on_board_count = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if (players[i].pieces[j].capturable == 1) {
				players[i].pieces[j].current_position = players[i].pieces[j].base_position; 	
				players[i].pieces[j].traveled_cells = 0; 	
				players[i].pieces[j].no_captured = 0; 	
				players[i].pieces[j].in_base = 1; 	
           			printf("Color %c piece %d lands on square %d, captures Color %c piece %d, and returns it to the base\n",player->playerid,piece_index, player->pieces[piece_index].current_position , players[i].playerid, j);
				if(players[i].pieces[j].in_base != 1){
					on_board_count +=1;
				}
				printf("%c player now has %d/4 of pieces on the board and %d/4 pieces on the base.\n", player->playerid, on_board_count, 4-on_board_count);
			}	
        	}
	}
}

// function for the coin toss to check the moving direction of a piece
int coin_toss() {
    return (rand() % 2);
}


void play(struct Player *player, int piece_index, int steps, struct Player players[]){
	land_on_same_cell(player, piece_index, steps, players);	
	int on_board_count = 0;
	for(int l=0; l<4; l++){
		if(player->pieces[l].in_base != 1){
			on_board_count += 1;
		}
	}

	if(player->pieces[piece_index].capture_ability == 1){
		player->pieces[piece_index].six_counter +=1;
		if(steps == 6){	
			if(player->pieces[piece_index].in_base ==1){	
				printf("%c moves piece %d to the starting point.\n", player->playerid, piece_index);
				take_out_base(player, piece_index, steps);
				player->pieces[piece_index].clockwise = coin_toss();
				capture_piece(player, piece_index, steps, players);
			}	
			else{		
				if(player->pieces[piece_index].finished !=1){
				if(player->pieces[piece_index].clockwise == 1){
					move_piece_forward(player, piece_index, steps);
				}
				else{
					move_piece_backward(player, piece_index, steps);
            			}
				capture_piece(player, piece_index, steps, players);
			} 
		}
	}
		else{
			if(player->pieces[piece_index].finished !=1){
				// Move the player's pieces by the dice roll value 
				if(player->pieces[piece_index].in_base != 1){
					if(player->pieces[piece_index].clockwise == 1){
	    					move_piece_forward(player, piece_index, steps);
            					}
					else{
	    					move_piece_backward(player, piece_index, steps);
					}
					capture_piece(player, piece_index, steps, players);
				}
			}
		}

		// Resetting the resutls of land_on_same_cell function
		player->pieces[piece_index].land_same_color_cell = 0;	
		player->pieces[piece_index].capture_ability = 0;	
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				players[i].pieces[j].capturable = 0; 
			}
		}
	}
	else{
		if(steps == 6){	
			if(player->pieces[piece_index].in_base ==1){
				printf("%c moves piece %d to the starting point.\n", player->playerid, piece_index);
				player->pieces[piece_index].six_counter +=1;
				take_out_base(player, piece_index, steps);
				player->pieces[piece_index].clockwise = coin_toss();
			}
		else{		
			if(player->pieces[piece_index].finished !=1){
					player->pieces[piece_index].six_counter +=1;
					if(player->pieces[piece_index].clockwise == 1){
						char direction[] = "clockwise";
            					printf("%c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
						move_piece_forward(player, piece_index, steps);
            					printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
					}
					else{
						char direction[] = "counter-clockwise";
            					printf("%c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
						move_piece_backward(player, piece_index, steps);
            					printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
					}
				} 
			}
		}

		else{
			if(player->pieces[piece_index].finished !=1){
				// Move the player's pieces  by the dice roll value
				if(player->pieces[piece_index].in_base != 1){
					if(player->pieces[piece_index].clockwise == 1){
						char direction[] = "clockwise";
        					printf("%c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
	    					move_piece_forward(player, piece_index, steps);
    						printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
					}	
					else{
						char direction[] = "counter-clockwise";
            					printf("%c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
	    					move_piece_backward(player, piece_index, steps);
            						printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
					}
				}
			}
		}

		// Resetting the resutls of land_on_same_cell function
		player->pieces[piece_index].land_same_color_cell = 0;	
		player->pieces[piece_index].capture_ability = 0;	
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				players[i].pieces[j].capturable = 0; 
			}
		}
	}
	
	on_board_count = 0;
	for(int l=0; l<4; l++){
		if(player->pieces[l].in_base != 1){
			on_board_count += 1;
		}
	}
	printf("%c player now has %d/4 of pieces on the board and %d/4 pieces on the base.\n\n", player->playerid, on_board_count, 4-on_board_count);
	
}

// Print the current game state for all players and their pieces
void print_game_state(struct Player players[]) {
	printf("----------------------------------------------\n");
	printf("----------------------------------------------\n");
    	for (int i = 0; i < 4; i++) {
        	printf("Player %c:\n", players[i].playerid);
        	for (int j = 0; j < 4; j++) {
			char place[10] = "";
			if(players[i].pieces[j].in_base == 1){
				strcpy(place, "in Base");
			}
			else if(players[i].pieces[j].finished == 1){
				strcpy(place, "in Home");
			}
			
            		//printf("  Piece %d - Current Position: %d, Traveled Cells: %d\n", 
            		printf("  Piece %d - Current Position: %d, %s\n", 
			players[i].pieces[j].pieceid, 
			players[i].pieces[j].current_position,
			place
                	/*,players[i].pieces[j].traveled_cells*/);
		}
	}
	printf("----------------------------------------------\n");
	printf("----------------------------------------------\n\n");
}

// Roll a dice and return a random number between 1 and 6
int roll_dice() {
    return (rand() % 6) + 1;
}

// Determine the starting player based on the highest roll
int determine_starting_player(int rolls[]) {
    int max_roll = rolls[0];
    int starting_player = 0;
    for (int i = 1; i < 4; i++) {
        if (rolls[i] > max_roll) {
            max_roll = rolls[i];
            starting_player = i;
        }
    }
    return starting_player;
}

// Determine the player order based on the starting player
void determine_player_order(int starting_player, int order[]) {
    // Player IDs: R = 0, G = 1, Y = 2, B = 3
    int player_id_order[4] = {0, 1, 2, 3};

    // Start filling the order array starting from the highest rolled player
    for (int i = 0; i < 4; i++) {
        order[i] = player_id_order[(starting_player + i) % 4];
    }
}


int rank = 0;  // Make sure rank is global or static if used across multiple function calls

int check_game_on(struct Player players[]) {    
    char winner[10] = "";
    int finished_player_count = 0; // Initialize count to zero

    for (int a = 0; a < 4; a++) {  // Iterate through each player
        int player_finished = 1; // Assume player is finished

        for (int b = 0; b < 4; b++) {  // Iterate through each piece of the player
            if (players[a].pieces[b].finished != 1) { // If any piece is not finished
                player_finished = 0; // Player is not finished
                break; // No need to check further pieces for this player
            }
        }

        if (player_finished) { // If all pieces are finished
            finished_player_count++; // Increment finished player count
        }

        // Update player rank if they are finished and rank hasn't been set
        if (player_finished && players[a].player_rank == 0) {
            rank++;  // Increment rank
            players[a].player_rank = rank;  // Assign rank to player
        }
    }

    if (finished_player_count == 3) { // If exactly three players are finished.
	/*
        for (int a = 0; a < 4; a++) {  // Iterate through each player
            if (players[a].player_rank != 0) {
                printf("Player %d rank = %d\n", a, players[a].player_rank);
            } else {
                printf("Player %d rank = 4\n", a);
            }
        }
	*/

        for (int t = 0; t < 4; t++) {  // Iterate through each player
            if (players[t].player_rank == 1) {
                if (t == 0) {
                    strcpy(winner, "Red");    
                } else if (t == 1) {
                    strcpy(winner, "Green");    
                } else if (t == 2) {
                    strcpy(winner, "Yellow");    
                } else if (t == 3) {
                    strcpy(winner, "Blue");    
                }
                printf("\nPlayer %s Wins !!!\n", winner);
            }
        }

        return 0; // Game ends
    }

    return 1; // Game continues
}


// function that generates a available mystery cell position
int old_mystery_cell = -20;
void mystery_cell_generate(struct Player players[]) {
        int mystery_cell;
	int is_occupied;
        do {
        // Generate a random number between 0 and 51
        mystery_cell = rand() % 52;
    	is_occupied = 0;
            
        // Check if the generated cell is occupied by any piece
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) { // Assuming each player has 4 pieces
            		if (players[i].pieces[j].current_position == mystery_cell || mystery_cell == old_mystery_cell) {
                		is_occupied = 1; // Cell is occupied
                        	break;
                	}
        	}
        	if (is_occupied) break; // Exit outer loop if cell is occupied
        } 
	} while (is_occupied); // Repeat until an unoccupied cell is found 
        // mystery_cell now contains an unoccupied cell
	old_mystery_cell = mystery_cell;
	printf("Mystery cell is :%d\n",mystery_cell);
}

/*
void activate_mystery(struct Player *player, int piece_index, struct Player players[]){
	int place_number = (rand() % 6) + 1;
	int teleported_cell_count =0;
	int toss;  // to check what happens in Bhawana (energized or sick)
	char place_name[30]="";
	if(place_number == 1){
		strcpy(place_name, "Bhawana");
		player->pieces[piece_index].current_position = 9; // 9 is the cell of the Bhawana
		toss = coin_toss();
		if(toss == 1){
			player->pieces[piece_index].energized= 1; // if toss is 1 then the player gets energized
		}
		else{
			player->pieces[piece_index].sick = 1; // if toss is 1 then the player gets energized
		}
		if(player->pieces[piece_index].clockwise == 1){
			if(player->pieces[piece_index].current_position <= 9){
				teleported_cell_count = 9 - player->pieces[piece_index].current_position ;
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}
			else{
				teleported_cell_count = 9 - player->pieces[piece_index].current_position +52;	
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}	
		}
		else{
			if(player->pieces[piece_index].current_position >= 9){
				teleported_cell_count = player->pieces[piece_index].current_position - 9 ;
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}
			else{
				teleported_cell_count = player->pieces[piece_index].current_position - 9 + 52;	
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}	
			
		}
		
	}
	else if(place_number == 2){
		strcpy(place_name, "Kotuwa");
		player->pieces[piece_index].current_position = 27; // 27 is the cell of the Kotuwa
		player->pieces[piece_index].kotuwa_paused = 1; // if toss is 1 then the player gets energized
		if(player->pieces[piece_index].clockwise == 1){
			if(player->pieces[piece_index].current_position <= 27){
				teleported_cell_count = 27 - player->pieces[piece_index].current_position ;
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}
			else{
				teleported_cell_count = 27 - player->pieces[piece_index].current_position +52;	
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}	
		}
		else{
			if(player->pieces[piece_index].current_position >= 27){
				teleported_cell_count = player->pieces[piece_index].current_position - 27;
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}
			else{
				teleported_cell_count = player->pieces[piece_index].current_position -27 + 52;	
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}	
		}
	}
	else if(place_number == 3){
		strcpy(place_name, "Pita-Kotuwa");
		player->pieces[piece_index].current_position = 46; // 46 is the cell of the Pita-Kotuwa
		if(player->pieces[piece_index].clockwise == 1){
			player->pieces[piece_index].clockwise = 0; // if toss is 1 then the player gets energized
			if(player->pieces[piece_index].current_position <= 46){
				teleported_cell_count = 46 - player->pieces[piece_index].current_position ;
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}
			else{
				teleported_cell_count = 46 - player->pieces[piece_index].current_position +52;	
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}	
		}
		else{
			if(player->pieces[piece_index].current_position >= 46){
				teleported_cell_count = player->pieces[piece_index].current_position - 46;
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}
			else{
				teleported_cell_count = player->pieces[piece_index].current_position - 46 + 52;	
				player->pieces[piece_index].traveled_cells += teleported_cell_count;
			}	
		}
	}
	else if(place_number == 4){
		strcpy(place_name, "Base");
		player->pieces[piece_index].current_position = player->pieces[piece_index].base_position; // teleport to the Base
		player->pieces[piece_index].traveled_cells = 0;  
		player->pieces[piece_index].no_captured = 0;  
	}
	else if(place_number == 5){
		strcpy(place_name, "X of the piece color");
		player->pieces[piece_index].current_position = player->pieces[piece_index].starting_position; // teleport to X position
		player->pieces[piece_index].traveled_cells = 0;  
	}
	else if(place_number == 6){
		strcpy(place_name, "Approach of the piece color");
		player->pieces[piece_index].current_position = player->pieces[piece_index].approach_position; // teleport to Approach position
		if(player->pieces[piece_index].clockwise == 1){
			player->pieces[piece_index].traveled_cells = 50;
		}
		else{
			player->pieces[piece_index].traveled_cells = 54;	
		}
	}
}

*/


//main game running function
void run_game() {
	// Initialize random number generator
    	initialize_random();

    	// Initialize players and pieces
    	struct Player players[4];
    	initialize_players(players);
    	printf("\nThe Red player has four (04) pieces named R1, R2, R3, and R4\n");
    	printf("The Green player has four (04) pieces named G1, G2, G3, and G4\n");
    	printf("The Yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
    	printf("The Blue player has four (04) pieces named B1, B2, B3, and B4\n\n");

    	// Each player rolls the dice to determine the starting player
    	int initial_rolls[4];
    	for (int i = 0; i < 4; i++) {
        	initial_rolls[i] = roll_dice();
        	printf("%c rolls %d\n", players[i].playerid, initial_rolls[i]);
    	}

    	// Determine the starting player based on the highest roll
    	int starting_player = determine_starting_player(initial_rolls);
    	printf("\n%c Player has the highest roll and will begin the game.\n", players[starting_player].playerid);

    	// Determine the player order based on the starting player
    	int player_order[4];
    	determine_player_order(starting_player, player_order);

    	// Display the player order
    	printf("\nThe order of a single round is: ");
    	for (int i = 0; i < 4; i++) {
        	printf("%c ", players[player_order[i]].playerid);
    	}
    	printf("\n");	

    	// Main gameplay loop until 3 players win
    	int game_on = 1;
    	int round = 0;
    	while (game_on) {
        	int piece_index = -1;
        	round++;
		int mystery_round=0;
        
        	printf("\nRound %d\n", round);
        	printf("-----------------------------------------------------\n");
		
		if(round>2 ){
			mystery_round = round;
			if((mystery_round+1)%4 == 0){
				mystery_cell_generate(players);
			}
		}
	
        	for (int i = 0; i < 4; i++) {
            	int current_player_index = player_order[i];
            	for (int j = 0; j < 2; j++) {
                	// Roll dice for the current player
                	int dice_roll = roll_dice();
                	printf("Player %c rolled a %d\n", players[current_player_index].playerid, dice_roll);

                	// Player Behaviors
                	piece_index = round % 4;
                	int loop_count = 0;
                	while ((((players[current_player_index].pieces[piece_index].in_base == 1 && dice_roll != 6) || players[current_player_index].pieces[piece_index].finished == 1) && loop_count < 4)) {
                    		loop_count++;
                    		piece_index = (piece_index + 1) % 4;

                    	if ((players[current_player_index].pieces[piece_index].in_base == 1 && dice_roll == 6) || ((players[current_player_index].pieces[piece_index].in_base != 1) && players[current_player_index].pieces[piece_index].finished != 1)) {
                        	break;
                    	}
               		}

                	// Main play start
                	play(&players[current_player_index], piece_index, dice_roll, players);

                	// Print updated game state
                	print_game_state(players);

                	// Stops repeating if six counter is not 0-1
                	if (players[current_player_index].pieces[piece_index].six_counter == 0 || players[current_player_index].pieces[piece_index].six_counter > 2) {
                    		break;
                	}
            	}

            	players[current_player_index].pieces[piece_index].six_counter = 0;
            	game_on = check_game_on(players);
            	printf("\n");
        	}
    	}

    	printf("Game Over!\n");
}
