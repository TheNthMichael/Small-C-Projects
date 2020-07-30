#include "Header.h"
// system("cls"); clears the screen used during update sequence
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>



// function signatures
void updateBoard(Cell board[BOARD_SIZE][BOARD_SIZE]);
Game updateGameStatus(Cell board[BOARD_SIZE][BOARD_SIZE], int* n_alive, int* n_dead);
void showBoard(Cell board[BOARD_SIZE][BOARD_SIZE]);
void fillBoard(Cell board[BOARD_SIZE][BOARD_SIZE]);


int main(int argc, char* argv[]) {
	int num_alive, num_dead;
	Cell board[BOARD_SIZE][BOARD_SIZE] = {0, D};
	Game state = C;
	fillBoard(board);

	int i = 0;

	do {
		printf("------- ITERATION: %d -------\n", i);
		// Output
		showBoard(board);
		// Run Algorithm
		updateBoard(board);
		// Update Game State
		state = updateGameStatus(board, &num_alive, &num_dead);
		// Clear Screen
		Sleep(FRAMES);
		if (state == C)
			SYS_CLEAR;
		i++;
	} while (state != L);
	puts("-----All Cells Are Empty-----");

	return 0;
}

void fillBoard(Cell board[BOARD_SIZE][BOARD_SIZE]) {
	srand(time(0));
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (rand() % 1000 < 30)
				board[i][j].state = A;
			else
				board[i][j].state = D;
		}
	}
}

// Run Game of Life Algorithm
void updateBoard(Cell board[BOARD_SIZE][BOARD_SIZE]) {
	//What bounds are we dealing with
			//Check if peice is 3 units away from all bounds if so, apply rules of life
			//If not, check how many units they have, if so apply rules of life to units available, treating the 3rd one as if it were dead.
	int neighbors = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			//get y
			if (i - 1 < 0 || i + 1 > BOARD_SIZE)
				neighbors = 0;
			//we know that there isn't space up or down
			else if (j - 1 < 0 || j + 1 > BOARD_SIZE)
				neighbors = 0;
			//we know that there isn't space to our left or right
			else if ((j - 1 >= 0 && j + 1 <= BOARD_SIZE - 1) && (i - 1 >= 0 && i + 1 <= BOARD_SIZE - 1)) {
				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {
						if (board[i + k][j + l].state == A)
							neighbors++;
					}
				}
			}
			board[i][j].number_of_neighbors = neighbors;
			neighbors = 0;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].number_of_neighbors > 3)
				board[i][j].state = D;
			else if (board[i][j].number_of_neighbors < 2)
				board[i][j].state = D;
			else if (board[i][j].state == 'D' && board[i][j].number_of_neighbors == 3)
				board[i][j].state = A;
			else
				board[i][j].state = A;
		}
	}
}

Game updateGameStatus(Cell board[BOARD_SIZE][BOARD_SIZE], int* n_alive, int* n_dead) {
	int temp_a = 0, temp_d = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].state == A)
				temp_a++;
			else
				temp_d++;
		}
	}
	(*n_alive) = temp_a;
	(*n_dead) = temp_d;
	if (temp_d == BOARD_SIZE * BOARD_SIZE)
		return L;
	else
		return C;
}

void showBoard(Cell board[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("\t");
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].state == A)
				printf("O ");
			else
				printf("- ");
		}
		printf("\n");
	}
}