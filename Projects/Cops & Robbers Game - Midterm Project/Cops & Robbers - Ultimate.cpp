/************************************************************
*	   Written & Developed By: Keivan Ipchi Hagh    		*
*	   Due Date: 11/6/2019									*
*	   Project Name: "Cops And Robber"      				*
*	   St.Number: 9831073									*
*	   Course: Fundamentals Of Programming In C				*
*	   OOP Steering Behavior Concept From "Nature Of Code"	*
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

/// C++ Standard Libraries
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

/// Objects
struct Police {
    int X, Y;
    char ID;
    int stationNumber;
    bool onRoute;
};

struct Robber {
    int X, Y;
    char ID;
    bool isCaught;
};

/// Function Declarations
void initializeCops(int, int, int, struct Police[]);
bool canIGoTo(int, int, bool, struct Police[], int, int, int);
bool gameOver(struct Police[], struct Robber, int);
void setOnRoute(struct Robber robber, struct Police[], int);
void SetColor(int);
void resetConsole();
void showInfo();

/// External Variables
int generations = 0;

/// Function: Main
int main() {

    showInfo();

    srand(time(NULL));
    int rowCount, columnCount;

    /// Get Row & Column Count
    printf(" - Enter Matrix Dimensions: ");
    scanf("%d%d", &rowCount, &columnCount);

    /// Initialize Matrix
    int Matrix[rowCount][columnCount];
    for (int i = 0; i < rowCount; i++)
        for (int j = 0 ; j < columnCount; j++)
            Matrix[i][j] = -2;

    /// Get Station Count
    int stationCount;
    printf(" - Enter The Number Of Stations: ");
    scanf("%d", &stationCount);

    /// Get Police Per Station
    int policePerStation[1000] = { -1 };
    int TotalCopsCount = 0;
    for (int i = 0; i < stationCount; i++) {
        int temp = 0;
        printf(" - Enter Number Of Cops For Station [%d]: ", i + 1);
        scanf("%d", &temp);
        TotalCopsCount += temp;
        policePerStation[i] = temp;
    }

    /// Define Objects
    struct Police cops[TotalCopsCount];
    struct Robber robber;
    robber.isCaught = false;

    /// Initialize Police Properties
    int tmpCnt1 = 0;
    for (int i = 0; i < stationCount; i++)
        for (int j = 0; j < policePerStation[i]; j++)
            cops[tmpCnt1++].stationNumber = i + 1;
    for (int i = 0; i < TotalCopsCount; i++) {
        cops[i].ID = 'D';   // How To Indicate A Cop On The Map
        cops[i].onRoute = false;    // Is The Cop On Route To The Suspect?
    }

    /// Set Location For Each Cop
    initializeCops(TotalCopsCount, rowCount, columnCount, cops);

    /// Initialize Robber Location
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

    resetConsole();

    while (true) {
        resetConsole(); // Reset Console

        ///* ----------------------- ROBBER MOVES ----------------------- *///

        bool escape = false;
        for (int i = 0; i < TotalCopsCount; i++)
            if (sqrt(pow(cops[i].X - robber.X, 2) + pow(cops[i].Y - robber.Y, 2) <= 2.82)) {
                /* "Nature Of Code" - "Reynolds Steering Behaviors" - OOP Concepts */
                Matrix[robber.X][robber.Y] = '\0';	// Reset Previous Location
                if (cops[i].Y - robber.Y != 0) {
                    int desiredVelocityY = robber.Y - cops[i].Y;
                    int steerY = desiredVelocityY / abs(desiredVelocityY);		// Normalize
                    if (canIGoTo(robber.Y + steerY, robber.X, true, cops, TotalCopsCount, rowCount, columnCount))
                        robber.Y += steerY;
                }

                if (cops[i].X - robber.X != 0) {
                    int desiredVelocityX = robber.X - cops[i].X;
                    int steerX = desiredVelocityX / abs(desiredVelocityX);		// Normalize
                    if (canIGoTo(robber.Y, robber.X + steerX, true, cops, TotalCopsCount, rowCount, columnCount))
                        robber.X += steerX;
                }
                escape = true;
                break;
            }

        if (!escape) {
            Matrix[robber.X][robber.Y] = '\0';	// Reset Previous Location
            while (true) {
                int velocityX = rand() % 3 - 1;	// -1? 0? +1?
                int velocityY = rand() % 3 - 1;	// -1? 0? +1?

                if (canIGoTo(robber.X + velocityX, robber.Y + velocityY, true, cops, TotalCopsCount, rowCount, columnCount) == true) {
                    Matrix[robber.X][robber.Y] = -2;
                    robber.X += velocityX;
                    robber.Y += velocityY;
                    break;
                }
            }
        }

        /// Communicate - Set Cops From The Same Stations On Route To The Suspect
        setOnRoute(robber, cops, TotalCopsCount);

        ///* ----------------------- COPS MOVES ----------------------- *///
        for (int i = 0; i < TotalCopsCount; i++) {
            float distance = sqrt(pow(cops[i].X - robber.X, 2) + pow(cops[i].Y - robber.Y, 2));		// Calculate Distance

            if ((distance <= 2.82 || cops[i].onRoute) && !robber.isCaught) {	    // Desired-Walk If Robber Is NOT Already Caught

                Matrix[cops[i].X][cops[i].Y] = -2;  // Reset Previous Location

                /* "Nature Of Code" - "Reynolds Steering Behaviors" - OOP Concepts */
                if (cops[i].Y - robber.Y != 0) {
                    int desiredVelocityY = robber.Y - cops[i].Y;
                    int steerY = desiredVelocityY / abs(desiredVelocityY);		// Normalize
                    cops[i].Y += steerY;
                }

                if (cops[i].X - robber.X != 0) {
                    int desiredVelocityX = robber.X - cops[i].X;
                    int steerX = desiredVelocityX / abs(desiredVelocityX);		// Normalize
                    cops[i].X += steerX;
                }

            } else {	// Random Walk

                Matrix[cops[i].X][cops[i].Y] = '\0';	// Reset Previous Move

                while (true) {
                    int velocityX = rand() % 3 - 1;	// -1? 0? +1?
                    int velocityY = rand() % 3 - 1;	// -1? 0? +1?

                    if (canIGoTo(cops[i].X + velocityX, cops[i].Y + velocityY, false, cops, TotalCopsCount, rowCount, columnCount)) {
                        Matrix[cops[i].X][cops[i].Y] = -2;
                        cops[i].X += velocityX;
                        cops[i].Y += velocityY;
                        break;
                    }
                }
            }

            /// Is Robber Caught? Then Don't Bother Following Him (Follow An Other Robber Instead) - OMG! THIS IS MAGIC!!! ;D
            if (robber.X == cops[i].X && robber.Y == cops[i].Y)
                robber.isCaught = true;
        }

        /// Determine Whether Robber Is Caught Or Not
        if (gameOver(cops, robber, TotalCopsCount))
            break;

        generations++;  // Increment Generations

        /// Reset OnRoute For Each Cop
        for (int i = 0; i < TotalCopsCount; i++)
            cops[i].onRoute = false;

        ///* ----------------------- DRAW MATRIX ----------------------- *///
        /// Add Cops To The Matrix
        for (int i = 0; i < TotalCopsCount; i++)
            Matrix[cops[i].X][cops[i].Y] = cops[i].stationNumber;

        /// Add Robber To The Matrix
        Matrix[robber.X][robber.Y] = (!robber.isCaught) ? 0 : -1;   // 0: Robber UnCaught, -1: Robber Caught

        SetColor(10);
        printf("\t# GENERATIONS: %d\n\n\n", generations);   // Show Generations

        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < columnCount; j++) {

                if (Matrix[i][j] > 0) {    // Cop
                    if (sqrt(pow(i - robber.X, 2) + pow(j - robber.Y, 2)) < 2.82)
                        SetColor(14);
                    else
                        SetColor(7);
                    printf("\tD%d\t", (Matrix[i][j]));
                }
                else if (Matrix[i][j] == 0) {
                    SetColor(12);
                    printf("\tT\t");
                } else if (Matrix[i][j] == -1)
                    printf("\tX\t");
                else
                    printf("\t \t");

                SetColor(8);
                if (j != columnCount - 1)
                    printf("|");
        }
            if (i != rowCount - 1) {
                printf("\n");
                for (int j = 0; j < columnCount; j++)
                    printf("  _____________ ");
                printf("\n\n");
            }
        }
        SetColor(7);

        Sleep(1000);
        printf("\n\n");
    }

    ///* ----------------------- ROBBER IS CAUGHT - SHOW RESULTS ----------------------- *///

    /// Add Cops To The Matrix
    for (int i = 0; i < TotalCopsCount; i++)
        Matrix[cops[i].X][cops[i].Y] = cops[i].stationNumber;

    /// Add Robber To The Matrix
    Matrix[robber.X][robber.Y] = (!robber.isCaught) ? 0 : -1;   // 0: Robber UnCaught, -1: Robber Caught

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            if (Matrix[i][j] > 0) {    // Cop
                printf("\tD%d\t", (Matrix[i][j]));
            }
            else if (Matrix[i][j] == 0 || Matrix[i][j] == -1) {
                SetColor(14);
                printf("\tX\t");
            }
            else
                printf("\t \t");

            SetColor(8);
            if (j != columnCount - 1)
                printf("|");
    }
        if (i != rowCount - 1) {
            printf("\n");
            for (int j = 0; j < columnCount; j++)
                printf("  _____________ ");
            printf("\n\n");
        }
    }
    SetColor(7);

	SetColor(9);
	printf("\n\n\t\t\t\t************************************************************      ");
	SetColor(13);
	printf("GAME OVER!");
	SetColor(9);
	printf("      ************************************************************\n");
	SetColor(10);
	printf("\t\t\t\t\t\t\t\t\t\t\tDeveloped By: Keivan Ipchi Hagh (;\n\t\t\t\t\t\t\t\t\t\t\t  Total Number Of Generations: %d\n", generations);
	SetColor(7);

    return 0;
}

/// Function: Set Cops Within The Range, On Route TO The Suspect
void setOnRoute(struct Robber robber, struct Police cops[], int TotalCopsCount) {
    for (int i = 0; i < TotalCopsCount; i++)
        if (sqrt(pow(cops[i].X - robber.X, 2) + pow(cops[i].Y - robber.Y, 2)) <= 2.82)
            for (int j = 0; j < TotalCopsCount; j++)
                if (cops[i].stationNumber == cops[j].stationNumber)
                    cops[j].onRoute = true;
}

/// Function: Initialize Cops Locations (No Duplicate Version)
void initializeCops(int TotalCopsCount, int rowCount, int columnCount, struct Police cops[]) {
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

/// Function: Check Corners
bool canIGoTo(int X, int Y, bool isRobber, struct Police cops[], int TotalCopsCount, int rowCount, int columnCount) {
	if (!isRobber) {	// It's A Cop
		if (X > 0 && X < columnCount && Y > 0 && Y < rowCount) {
			for (int i = 0 ; i < TotalCopsCount; i++)
				if (X == cops[i].X && Y == cops[i].Y)
					return false;
			return true;
		}
		else
			return false;
	} else	// It's A Robber
		if (X > 0 && X < columnCount && Y > 0 && Y < rowCount)
			return true;
		else
			return false;
}

/// Function: Determine If Cops Have Caught The Robber Or Not
bool gameOver(struct Police cops[], struct Robber robber, int TotalCopsCount) {
	for (int i = 0; i < TotalCopsCount; i++)
		if (cops[i].X == robber.X && cops[i].Y == robber.Y)
			return true;
	return false;
}

/// Function: Set Color For Output
void SetColor(int ForgC) {

 	WORD wColor;
  	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  	CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word - /Mask out all but the background attribute, and add in the forgournd color
 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
      	SetConsoleTextAttribute(hStdOut, (csbi.wAttributes & 0xF0) + (ForgC & 0x0F));
}

/// Function: Reset Console & Re-Draw Template
void resetConsole() {
	//system("cls");	// Reset Prompt
	SetColor(3);
	printf("----------------------------------------------------------------------------------------------- COPS AND ROBBERS ------------------------------------------------------------------------------------------------\n\n");
	SetColor(7);
}

/// Function: Show Project Info & Change Visual
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

	resetConsole();
}
