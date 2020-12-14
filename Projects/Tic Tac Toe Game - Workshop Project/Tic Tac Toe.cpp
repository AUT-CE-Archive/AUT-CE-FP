// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global Variables
int const dementions = 3;
char matrix[dementions][dementions];

// Functions
void draw();
char isGameOver();
void initMatrix();
bool canMove(int);
bool move(int, char);

int main() {
	
	initMatrix();
	int counter = 0;
	int step = 0;
	
	while (true) {		
		int location;		
		if (counter % 2 == 0) {	// Player X			
			z:;
			printf("Player X: ");
			scanf("%d", &location);
			printf("\n");
						
			if (!(canMove(location) && move(location, 'X'))) {
				draw();
				printf("Cannot Make The Move, Try Again.\n");
				goto z;
			}				
			draw();
			step++;
		
		} else {	// Player O		
			t:;
			printf("Player O: ");	
			scanf("%d", &location);
			printf("\n");
			
			if (!(canMove(location) && move(location, 'O'))) {
				draw();
				printf("Cannot Make The Move, Try Again.\n");
				goto t;
			}				
			draw();
			step++;
		}
		
		if (isGameOver() == 'X') {
			system("cls");
			draw();
			printf("Player 1 Wins!!!");
			break;
		} else if (isGameOver() == 'O') {
			system("cls");
			draw();
			printf("Player 2 Wins!!!");
			break;
		}
		
		if (step == 9) {
			system("cls");
			draw();
			printf("No Winner - Game Withdraw!!!");
			break;
		}
		counter++;
	}			
	
	return 0;
}

// Function: Can Move To Determine Whether Location Is Empty
bool canMove(int location) {
	switch (location) {
		case 1: return (matrix[0][0] == ' ') ? true : false; break;
		case 2: return (matrix[0][1] == ' ') ? true : false; break;
		case 3: return (matrix[0][2] == ' ') ? true : false; break;
		case 4: return (matrix[1][0] == ' ') ? true : false; break;
		case 5: return (matrix[1][1] == ' ') ? true : false; break;
		case 6: return (matrix[1][2] == ' ') ? true : false; break;
		case 7: return (matrix[2][0] == ' ') ? true : false; break;
		case 8: return (matrix[2][1] == ' ') ? true : false; break;
		case 9: return (matrix[2][2] == ' ') ? true : false; break;
		default: return false;
	}
}

// Function: Move - Return True If Move Is Successful, Return False Otherwise
bool move(int location, char player) {	
	switch (location) {
		case 1: matrix[0][0] = player; return true; break;	
		case 2: matrix[0][1] = player; return true; break;
		case 3: matrix[0][2] = player; return true; break;
		case 4: matrix[1][0] = player; return true; break;
		case 5: matrix[1][1] = player; return true; break;
		case 6: matrix[1][2] = player; return true; break;
		case 7: matrix[2][0] = player; return true; break;
		case 8: matrix[2][1] = player; return true; break;
		case 9: matrix[2][2] = player; return true; break;
		default: return false; break;
	}
}

// Function: Initialize Matrix
void initMatrix() {
	for (int i = 0; i < dementions; i++)
		for (int j = 0; j < dementions; j++)
			matrix[i][j] = ' ';
}

// Function: Draw
void draw() {
	for (int i = 0; i < dementions; i++) {
		printf(" %c | %c | %c", matrix[i][0], matrix[i][1], matrix[i][2]);
		printf("\n\n");
	}
	printf("\n\n");
}

// Function: Check If Game In Over
char isGameOver() {
	if (matrix[0][0] == matrix[0][1] && matrix[0][1] == matrix[0][2] && matrix[0][2] == 'X')	// Horizonal
		return 'X';
	else if (matrix[0][0] == matrix[0][1] && matrix[0][1] == matrix[0][2] && matrix[0][2] == 'O')	// Horizonal
		return 'O';
	else if (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2] && matrix[1][2] == 'X')	// Horizonal
		return 'X';
	else if (matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2] && matrix[1][2] == 'O')	// Horizonal
		return 'O';	
	else if (matrix[2][0] == matrix[2][1] && matrix[2][1] == matrix[2][2] && matrix[2][2] == 'X')	// Horizonal
		return 'X';
	else if (matrix[2][0] == matrix[2][1] && matrix[2][1] == matrix[2][2] && matrix[2][2] == 'O')	// Horizonal
		return 'O';
	else if (matrix[0][0] == matrix[1][0] && matrix[1][0] == matrix[2][0] && matrix[2][0] == 'X')	// Vertical
		return 'X';
	else if (matrix[0][0] == matrix[1][0] && matrix[1][0] == matrix[2][0] && matrix[2][0] == 'O')	// Vertical
		return 'O';
	else if (matrix[0][1] == matrix[1][1] && matrix[1][1] == matrix[2][1] && matrix[2][1] == 'X')	// Vertical
		return 'X';
	else if (matrix[0][1] == matrix[1][1] && matrix[1][1] == matrix[2][1] && matrix[2][1] == 'O')	// Vertical
		return 'O';
	else if (matrix[0][2] == matrix[1][2] && matrix[1][2] == matrix[2][2] && matrix[2][2] == 'X')	// Vertical
		return 'X';
	else if (matrix[0][2] == matrix[1][2] && matrix[1][2] == matrix[2][2] && matrix[2][2] == 'O')	// Vertical
		return 'O';
	else if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[2][2] == 'X')	// Diagonal
		return 'X';
	else if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[2][2] == 'O')	// Diagonal
		return 'O';
	else if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[2][0] == 'X')	// Diagonal
		return 'X';
	else if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[2][0] == 'O')	// Diagonal
		return 'O';	
	else
		return ' ';
}
