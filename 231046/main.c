#include "types.h"
#include <stdio.h>

int main() {
	int game_on = 1;
	int round = 0;
	struct Player players[4];
	int player_order[4];
	int initial_rolls[4];
	
	// this function holds the main loop of the game
	run_game();	
}


