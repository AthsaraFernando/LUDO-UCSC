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
    // Initialize Player R (Red)
    players[0].playerid = 'R';
    for (int i = 0; i < 4; i++) {
        players[0].pieces[i].pieceid = i;
        players[0].pieces[i].current_position = -1;
        players[0].pieces[i].base_position = -1;
        players[0].pieces[i].traveled_cells = 0;
        players[0].pieces[i].starting_position = 28;
        players[0].pieces[i].home_start = 95;
        players[0].pieces[i].no_captured = 0;
        players[0].pieces[i].approach_position = 26;
        players[0].pieces[i].six_counter = 0;
        players[0].pieces[i].clockwise = 1;
        players[0].pieces[i].in_base = 1;
        players[0].pieces[i].land_same_color_cell = 0;
        players[0].pieces[i].capturable = 0;
        players[0].pieces[i].capture_ability = 0;
        players[0].pieces[i].is_rolling_piece = 0;
        players[0].pieces[i].finished = 0;
    }

    // Initialize Player G (Green)
    players[1].playerid = 'G';
    for (int i = 0; i < 4; i++) {
        players[1].pieces[i].pieceid = i;
        players[1].pieces[i].current_position = -2;
        players[1].pieces[i].base_position = -2;
        players[1].pieces[i].traveled_cells = 0;
        players[1].pieces[i].starting_position = 41;
        players[1].pieces[i].home_start = 195;
        players[1].pieces[i].no_captured = 0;
        players[1].pieces[i].approach_position = 39;
        players[1].pieces[i].six_counter = 0;
        players[1].pieces[i].clockwise = 1;
        players[1].pieces[i].in_base = 1;
        players[1].pieces[i].land_same_color_cell = 0;
        players[1].pieces[i].capturable = 0;
        players[1].pieces[i].capture_ability = 0;
        players[1].pieces[i].is_rolling_piece = 0;
        players[1].pieces[i].finished = 0;
    }

    // Initialize Player Y (Yellow)
    players[2].playerid = 'Y';
    for (int i = 0; i < 4; i++) {
        players[2].pieces[i].pieceid = i;
        players[2].pieces[i].current_position = -3;
        players[2].pieces[i].base_position = -3;
        players[2].pieces[i].traveled_cells = 0;
        players[2].pieces[i].starting_position = 2;
        players[2].pieces[i].home_start = 295;
        players[2].pieces[i].no_captured = 0;
        players[2].pieces[i].approach_position = 0;
        players[2].pieces[i].six_counter = 0;
        players[2].pieces[i].clockwise = 1;
        players[2].pieces[i].in_base = 1;
        players[2].pieces[i].land_same_color_cell = 0;
        players[2].pieces[i].capturable = 0;
        players[2].pieces[i].capture_ability = 0;
        players[2].pieces[i].is_rolling_piece = 0;
        players[2].pieces[i].finished = 0;
    }

    // Initialize Player B (Blue)
    players[3].playerid = 'B';
    for (int i = 0; i < 4; i++) {
        players[3].pieces[i].pieceid = i;
        players[3].pieces[i].current_position = -4;
        players[3].pieces[i].base_position = -4;
        players[3].pieces[i].traveled_cells = 0;
        players[3].pieces[i].starting_position = 15;
        players[3].pieces[i].home_start = 395;
        players[3].pieces[i].no_captured = 0;
        players[3].pieces[i].approach_position = 13;
        players[3].pieces[i].six_counter = 0;
        players[3].pieces[i].clockwise = 1;
        players[3].pieces[i].in_base = 1;
        players[3].pieces[i].land_same_color_cell = 0;
        players[3].pieces[i].capturable = 0;
        players[3].pieces[i].capture_ability = 0;
        players[3].pieces[i].is_rolling_piece = 0;
        players[3].pieces[i].finished = 0;
    }
}

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
                printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
            
			}	
        	}}
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
                printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
            
			}	
        	}}

	}
}


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
        }}


}

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
				if(player->pieces[piece_index].clockwise == 1){
					move_piece_forward(player, piece_index, steps);
				}
				else{
					move_piece_backward(player, piece_index, steps);
            			}
				capture_piece(player, piece_index, steps, players);
			} 
		}
		else{
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
				player->pieces[piece_index].six_counter +=1;
				if(player->pieces[piece_index].clockwise == 1){
					char direction[] = "clockwise";
            				printf(" %c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
					move_piece_forward(player, piece_index, steps);
            				printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
				}
				else{
					char direction[] = "counter-clockwise";
            				printf(" %c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
					move_piece_backward(player, piece_index, steps);
            				printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
				}
			} 
		}
		else{
			// Move the player's pieces  by the dice roll value
			if(player->pieces[piece_index].in_base != 1){
				if(player->pieces[piece_index].clockwise == 1){
					char direction[] = "clockwise";
        				printf(" %c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
	    				move_piece_forward(player, piece_index, steps);
    					printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
				}	
				else{
					char direction[] = "counter-clockwise";
            				printf(" %c Player moves piece %d from location %d ", player->playerid, piece_index ,player->pieces[piece_index].current_position);
	    				move_piece_backward(player, piece_index, steps);
            					printf("to %d by %d units %s direction\n",player->pieces[piece_index].current_position, steps, direction);
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

int check_game_on(struct Player players[]) {
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
    }

    if (finished_player_count == 3) { // If exactly three players are finished
        return 0; // Game ends
    }

    return 1; // Game continues
}

