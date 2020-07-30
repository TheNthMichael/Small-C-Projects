#pragma once
// Resources

#define SYS_CLEAR system("cls")

#define BOARD_SIZE 26
#define FRAMES 100


enum state {D, A};	// Each cell is either dead or alive
enum game_state {L, C};	
// The game is either over if all cells are deas since this means that we cannot populate the board any further,
//	otherwise the game is in a continuous state that updates
typedef enum state State;
typedef enum game_state Game;

typedef struct cell Cell;
struct cell {
	int number_of_neighbors;
	State state;
};