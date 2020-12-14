/****************************************************
*	   Written & Developed By: Keivan Ipchi Hagh    *
*	   Due Date: 11/6/2019							*
*	   Project Name: 'Cops And Robber'      		*
*	   St.Number: 9831073							*
*	   Course: Fundementals Of Programming In C		*
*****************************************************/

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

static void robbeRandomWalk();

// Global Variables

Robber robber;

const int rowCount = 7;
const int columnCount = 7;
static char matrix[rowCount][columnCount];
static int stationCount;
static int TotalCopsCount = 0;

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
				case 0: cops[index].symbol = 'A'; cops[index].colorID = 13; break;
				case 1: cops[index].symbol = 'B'; cops[index].colorID = 2; break;
				case 2: cops[index].symbol = 'C'; cops[index].colorID = 3; break;
				case 3: cops[index].symbol = 'D'; cops[index].colorID = 14; break;
				case 4: cops[index].symbol = 'E'; cops[index].colorID = 5; break;
				case 5: cops[index].symbol = 'F'; cops[index].colorID = 6; break;
				case 6: cops[index].symbol = 'G'; cops[index].colorID = 7; break;
				case 7: cops[index].symbol = 'H'; cops[index].colorID = 9; break;
				case 8: cops[index].symbol = 'I'; cops[index].colorID = 10; break;
				case 9: cops[index].symbol = 'J'; cops[index].colorID = 11; break;
			}			
			index++;	
		}				
	}	
	
	resetConsole();		// Reset Console			
	initializeMatrix();			// Initialize Matrix
	initializeCops(cops);		// Initialzie Cops
	initializeRobber(cops);		// Initialize Robber		
	
	drawMatrix(cops);				
	return 0;	
}

// Function: Robbers Random Walk
void robbeRandomWalk() {
	
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
	matrix[robber.X][robber.Y] = robber.symbol;
	
	// Draw Matrix
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < columnCount; j++) {
			
			if (matrix[i][j] == 'T')
				SetColor(robber.colorID);
				
			switch(matrix[i][j]) {
				case 'A': SetColor(13); break;
				case 'B': SetColor(2); break;
				case 'C': SetColor(3); break;
				case 'D': SetColor(14); break;
				case 'E': SetColor(5); break;
				case 'F': SetColor(6); break;
				case 'G': SetColor(7); break;
				case 'H': SetColor(9); break;
				case 'I': SetColor(10); break;
				case 'J': SetColor(11); break;
			}
			
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
