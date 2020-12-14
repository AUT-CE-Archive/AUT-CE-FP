/************************************************************
*	   Written & Developed By: Keivan Ipchi Hagh    		*
*	   Due Date: 11/6/2019									*
*	   Project Name: 'Cops And Robber'      				*
*	   St.Number: 9831073									*
*	   Course: Fundementals Of Programming In C				*
*	   OOP Steering Behavior Taken From 'Nature Of COde'	*
*************************************************************/

/*  --- Coloring Guide ---
	Black        |   0
	Blue         |   1
	Green        |   2
	Cyan         |   3
	Red          |   4
	Magenta      |   5
	Brown        |   6
	Light Gray   |   7
	Dark Gray    |   8
	Light Blue   |   9
	Light Green  |   10
	Light Cyan   |   11
	Light Red    |   12
	Light Magenta|   13
	Yellow       |   14
	White        |   15
*/

// C Standard Libraries
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#include <ctime>

// Objects
class Robber {
	public:
	int colorID = 12;
	char symbol = 'T';
	int X, Y;
};

class Cop {
	public:
	int colorID;
	char symbol;
	bool targetDetected;
	int X, Y;
};

// Function Declarations
static void resetConsole();
static void drawMatrix(Cop[]);
static void SetColor(int);
static void showInfo();

static void initializeMatrix();
static void initializeRobber(Cop[]);
static void initializeCops(Cop[]);

static void action(Cop[]);
static void robberRandomWalk();
static void copsWalk(Cop[]);
static bool canIGoTo(int, int, bool);
static bool gameOver(Cop[]);

// Objects
Robber robber;

// Global Variables
const int rowCount = 7;
const int columnCount = 7;
static char matrix[rowCount][columnCount];

static int stationCount;
static int TotalCopsCount = 0;
static bool isCaught = false;

// Function: Main
int main() {
	
	showInfo();		// Show Project Info & Change Visual
	
	// Get Station Count
	printf(" - Enter Number Of Police Stations (Max 10): ");
	scanf("%d", &stationCount);
	
	// Get & Initialize Cops
	int station[stationCount];	
	for (int i = 0; i < stationCount; i++) {
		printf(" - Enter Police Count For Station [%d]: ", i + 1);
		scanf("%d", &station[i]);
		TotalCopsCount += station[i];				
	}	
	// Cops Array
	Cop cops[TotalCopsCount];
	
	int index = 0;
	for (int i = 0; i < stationCount; i++) {		
	
		for (int j = 0; j < station[i]; j++) {
			char symbol;
			switch(i) {
				case 0: cops[index].symbol = 'A'; break;
				case 1: cops[index].symbol = 'B'; break;
				case 2: cops[index].symbol = 'C'; break;
				case 3: cops[index].symbol = 'D'; break;
				case 4: cops[index].symbol = 'E'; break;
				case 5: cops[index].symbol = 'F'; break;
				case 6: cops[index].symbol = 'G'; break;
				case 7: cops[index].symbol = 'H'; break;
				case 8: cops[index].symbol = 'I'; break;
				case 9: cops[index].symbol = 'J'; break;
			}			
			index++;	
		}				
	}	
	
	resetConsole();		// Reset Console
	initializeMatrix();			// Initialize Matrix	
	initializeCops(cops);		// Initialzie Cops
	initializeRobber(cops);		// Initialize Robber			
		
	action(cops);	
	
	return 0;	
}

// Funtion: Main Function For Movements
void action(Cop cops[]) {
	
	while (!gameOver(cops)) {		
		resetConsole();				
		robberRandomWalk();		// Move Robber Randomly
		drawMatrix(cops);	// Draw Map 
		Sleep(1000);
		
		resetConsole();
		copsWalk(cops);		// Move Cops Randomly & With Desired Vel					
		drawMatrix(cops);	// Draw Map 
		Sleep(1000);
	}
	// Show Last Move
	isCaught = true;
	resetConsole();
	drawMatrix(cops);
	
	printf("\n\t\t\t\t\t\t\tGAME OVER!\t\t\t\t\t\n");
}

// Function: Cops Walk Randomly & With A Desired Velocity
void copsWalk(Cop cops[]) {
	
	for (int i = 0; i < TotalCopsCount; i++) {
				
		float distance = sqrt(pow(cops[i].X - robber.X, 2) + pow(cops[i].Y - robber.Y, 2));		// Calculate Distance
		
		if (distance <= 2) {	// Desired-Walk		
			
		cops[i].colorID = 14;	// Set Color ID
		matrix[cops[i].X][cops[i].Y] = '\0';  // Reset Previous Location
		
		/* 'Nature Of Code' - 'Rynolds Steering Behaviors' - OOP Concepts */
		if (cops[i].X - robber.X != 0 && cops[i].Y - robber.Y != 0) {
			
			int desiredVelocityX = robber.X - cops[i].X;			
			if (desiredVelocityX > 0)
				cops[i].X += 1;
			else if (desiredVelocityX < 0)
				cops[i].X -= 1;
				
			int desiredVelocityY = robber.Y - cops[i].Y;
			if (desiredVelocityY > 0)
				cops[i].Y += 1;
			else if (desiredVelocityY < 0)
				cops[i].Y -= 1;
			
		} else if (cops[i].X - robber.X == 0 && cops[i].Y - robber.Y != 0) {
			int desiredVelocity = robber.Y - cops[i].Y;
			if (desiredVelocity > 0)
				cops[i].Y += 1;
			else if (desiredVelocity < 0)
				cops[i].Y -= 1;
			
		} else if (cops[i].X - robber.X != 0 && cops[i].Y - robber.Y == 0) {
			int desiredVelocity = robber.X - cops[i].X;
			if (desiredVelocity > 0)
				cops[i].X += 1;
			else if (desiredVelocity < 0)
				cops[i].X -= 1;
		}
			
		} else {	// Random Walk			
			
			cops[i].colorID = 7;	// Set Color ID
			matrix[cops[i].X][cops[i].Y] = '\0';	// Reset Previous Move
			srand((time(0)));

			z:;
			int velocityX = rand() % 3 - 1;	// -1? 0? +1?
			int velocityY = rand() % 3 - 1;	// -1? 0? +1?
	
			if (canIGoTo(cops[i].X + velocityX, cops[i].Y + velocityY, false) == true) {
				cops[i].X += velocityX; 
				cops[i].Y += velocityY;	
			} else
				goto z;	
		}		
	}
	
}

// Funtion: Determine If Cops Have Caught The Robber Or Not
bool gameOver(Cop cops[]) {
	for (int i = 0; i < TotalCopsCount; i++)
		if (cops[i].X == robber.X && cops[i].Y == robber.Y)
			return true;
	return false;
}

// Function: Robbers Random Walk
void robberRandomWalk() {
	
	matrix[robber.X][robber.Y] = '\0';	// Reset Previous Location
	srand(time(NULL));
	
	z:;
	int velocityX = rand() % 3 - 1;	// -1? 0? +1?
	int velocityY = rand() % 3 - 1;	// -1? 0? +1?
	
	if (canIGoTo(robber.X + velocityX, robber.Y + velocityY, true) == true) {
		robber.X += velocityX; 
		robber.Y += velocityY;		
	} else
		goto z;	
}

// Function: Check Corners
bool canIGoTo(int X, int Y, bool isRobber) {
			
	if (!isRobber) {	// It's A Cop
		if (X > 0 && X < columnCount && Y > 0 && Y < columnCount && (matrix[X][Y] != 'A' && matrix[X][Y] != 'B' && matrix[X][Y] != 'C' && matrix[X][Y] != 'D' && matrix[X][Y] != 'E' && matrix[X][Y] != 'F' && matrix[X][Y] != 'G' && matrix[X][Y] != 'H' && matrix[X][Y] != 'I' & matrix[X][Y] != 'J'))
			return true;
		
	else
		return false;
	} else {	// It's A Robber
		if (X > 0 && X < columnCount && Y > 0 && Y < columnCount)
			return true;
		else
			return false;
	}	
}

// Function: Show Project Info & Change Visual
void showInfo() {
	SetConsoleTitle("COPS AND ROBBERS - Written By Keivan Ipchi Hagh");		// Change Console Title
	
	resetConsole();		// Reset Console
	SetColor(10);
	printf(" $ Project Name:\t\t'Cops And Robbers'\n");
	Sleep(500);
	printf(" $ Written And Developed By:\t'Keivan Ipchi Hagh'\n");
	Sleep(500);
	printf(" $ Due Date:\t\t\t'December 7, 2019'\n");
	Sleep(500);
	printf(" $ Course Prof:\t\t\t'Dr.Ehsan Nazerfard'\n\n");
	Sleep(500);
	SetColor(7);
}

// Function: Initialize Robber (No Duplicate Version)
void initializeRobber(Cop cops[]) {
	
	srand(time(NULL));
	int randX = rand() % columnCount;
	int randY = rand() % rowCount;
		
	for (int i = 0; i < TotalCopsCount;) {
		if (cops[i].X == randX && cops[i].Y == randY) {
			randX = rand() % columnCount;
			randY = rand() % rowCount;
			i = 0;
		} else
			i++;
	}	
	
	robber.X = randX;
	robber.Y = randY;
}

// Function: Initialize Cops (No Duplicate Version)
void initializeCops(Cop cops[]) {			
		
	srand(time(NULL));
	for (int i = 0; i < TotalCopsCount; i++) {
		
		z:;
		int randX = rand() % columnCount;
		int randY = rand() % rowCount;
		
		for (int j = 0; j < TotalCopsCount; j++) 
			if (randX == cops[j].X && randY == cops[j].Y)
				goto z;
		cops[i].X = randX;
		cops[i].Y = randY;
	}
}

// Function: Draw Matrix (Map)
void drawMatrix(Cop cops[]) {
	
	// Add Cops To The Matrix
	for (int i = 0; i < TotalCopsCount; i++)
		matrix[cops[i].X][cops[i].Y] = cops[i].symbol;
		
	// Add Robber To The Matrix
	if (!isCaught)
		matrix[robber.X][robber.Y] = robber.symbol;
	else
		matrix[robber.X][robber.Y] = 'X';
	
	// Draw Matrix
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < columnCount; j++) {
						
			if (matrix[i][j] == 'T')
				SetColor(robber.colorID);	// Robbers Coller
			else if (matrix[i][j] == 'T' && isCaught == true)
				SetColor(3);
			else if (sqrt(pow(i - robber.X, 2) + pow(j - robber.Y, 2)) <= 2)
				SetColor(14);
			else
				SetColor(7);	// Cops Color
			
			if (j != columnCount - 1) {				
				printf("\t%c\t", matrix[i][j]);
				SetColor(8);
				printf("|");
			}				
			else {
				printf("\t%c\t", matrix[i][j]);
			}				
		}
		SetColor(8);
		if (i != rowCount - 1) {
			printf("\n");		
			for (int k = 0; k < columnCount; k++)
				printf("  _____________ ");
			printf("\n\n");
		}			
	}
	SetColor(7);
	printf("\n\n\n");
}

// Function: Initialize Matrix (Map)
void initializeMatrix() {
	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < columnCount; j++)
			matrix[i][j] = '\0';	// NULL
}

// Function: Set Color For Output
void SetColor(int ForgC) {
 	WORD wColor;
		
  	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  	CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		//Mask out all but the background attribute, and add in the forgournd color
      	wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      	SetConsoleTextAttribute(hStdOut, wColor);
 	}
}

// Function: Reset Console & Re-Draw Template
void resetConsole() {
	system("cls");	// Reset Prompt
	SetColor(3);
	printf("------------------------------------------------- COPS AND ROBBERS --------------------------------------------------\n\n");
	SetColor(7);
}
