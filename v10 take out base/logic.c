#include "types.h"
#include <stdio.h>
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
        players[0].pieces[i].traveled_cells = 0;
        players[0].pieces[i].starting_position = 28;
        players[0].pieces[i].home_start = 95;
        players[0].pieces[i].no_captured = 0;
        players[0].pieces[i].approach_position = 26;
        players[0].pieces[i].approach_counter = 0;
        players[0].pieces[i].six_counter = 0;
        players[0].pieces[i].in_base = 1;
    }

    // Initialize Player G (Green)
    players[1].playerid = 'G';
    for (int i = 0; i < 4; i++) {
        players[1].pieces[i].pieceid = i;
        players[1].pieces[i].current_position = -2;
        players[1].pieces[i].traveled_cells = 0;
        players[1].pieces[i].starting_position = 41;
        players[1].pieces[i].home_start = 195;
        players[1].pieces[i].no_captured = 0;
        players[1].pieces[i].approach_position = 39;
        players[1].pieces[i].approach_counter = 0;
        players[1].pieces[i].six_counter = 0;
        players[1].pieces[i].in_base = 1;
    }

    // Initialize Player Y (Yellow)
    players[2].playerid = 'Y';
    for (int i = 0; i < 4; i++) {
        players[2].pieces[i].pieceid = i;
        players[2].pieces[i].current_position = -3;
        players[2].pieces[i].traveled_cells = 0;
        players[2].pieces[i].starting_position = 2;
        players[2].pieces[i].home_start = 295;
        players[2].pieces[i].no_captured = 0;
        players[2].pieces[i].approach_position = 0;
        players[2].pieces[i].approach_counter = 0;
        players[2].pieces[i].six_counter = 0;
        players[2].pieces[i].in_base = 1;
    }

    // Initialize Player B (Blue)
    players[3].playerid = 'B';
    for (int i = 0; i < 4; i++) {
        players[3].pieces[i].pieceid = i;
        players[3].pieces[i].current_position = -4;
        players[3].pieces[i].traveled_cells = 0;
        players[3].pieces[i].starting_position = 15;
        players[3].pieces[i].home_start = 395;
        players[3].pieces[i].no_captured = 0;
        players[3].pieces[i].approach_position = 13;
        players[3].pieces[i].approach_counter = 0;
        players[3].pieces[i].in_base = 1;
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
	
}

// Placeholder function for moving the specified piece backward
void move_piece_backward(struct Player *player, int piece_index, int steps) {
    // Implementation will be provided later
}

void play(struct Player *player, int piece_index, int steps){
	if(steps == 6){
		if(player->pieces[piece_index].in_base ==1){
			take_out_base(player, piece_index, steps);
		}
		else{
			player->pieces[piece_index].six_counter +=1;
			// Move the player's piece 0 by the dice roll value
            		printf("Moving Player %c's piece 0 by %d steps...\n", player->playerid, steps);
			move_piece_forward(player, piece_index, steps);
		}
	}
	else{
		// Move the player's piece 0 by the dice roll value
            	printf("Moving Player %c's piece 0 by %d steps...\n", player->playerid, steps); 
	    	move_piece_forward(player, piece_index, steps);
	}
}

// Print the current game state for all players and their pieces
void print_game_state(struct Player players[]) {
    for (int i = 0; i < 4; i++) {
        printf("Player %c:\n", players[i].playerid);
        for (int j = 0; j < 4; j++) {
            printf("  Piece %d - Current Position: %d, Traveled Cells: %d\n", 
                   players[i].pieces[j].pieceid, 
                   players[i].pieces[j].current_position, 
                   players[i].pieces[j].traveled_cells);
        }
    }
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


