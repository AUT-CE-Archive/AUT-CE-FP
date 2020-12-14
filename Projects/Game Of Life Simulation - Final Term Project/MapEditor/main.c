///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Map Editor                          ///
///*********************************************************///

/*  --- Coloring Guide ---
	Black           |   0
	Blue            |   1
	Green           |   2
	Cyan            |   3
	Red             |   4
	Magenta         |   5
	Brown           |   6
	Light Gray      |   7
	Dark Gray       |   8
	Light Blue      |   9
	Light Green     |   10
	Light Cyan      |   11
	Light Red       |   12
	Light Magenta   |   13
	Yellow          |   14
	White           |   15
*/

/// C & C++ Standard Libraries
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <math.h>

/// Add-On Libraries
#include "MapGenerator.h"

/// Function Declarations
void SetColor(int);
void EditMap(int mapSize, Blocks blockMatrix[][mapSize]);
void showVisualMap(int mapSize, Blocks blockMatrix[][mapSize]);
void setCellColor(int mapSize, int i, int j, Blocks blockMatrix[][mapSize]);
void createNewMap_Header(void);
void editExistingMap_Header(void);
void showHorizontalRuler(int index);

int main() {

    int optionSelection;
    unsigned int mapSize;

	SetConsoleTitle("Map Editor version 2.4 - Developed By: Keivan Ipchi Hagh");
    SetColor(9);
    printf(" ----------------------------------------- WELCOME TO MAP EDITOR VERSION 2.4 -----------------------------------------\n\n");

    /// Setting up Console:
    SetColor(6);
    printf("Setting Up Console: ");
    system("chcp 65001");
    printf("UTF-8 Encoding Set.");
    SetColor(15);
    printf("\n\nPlease Choose Your Action:\n1) Create A New Map\n2) Create Random Map (Map Engine V2)\n3) Edit An Existing Map\n4) Exit");

    /// User Options Selection
    z:;
    SetColor(15);
    printf("\n\nOption Selection [1-3]: ");
    SetColor(3);
    scanf("%d", &optionSelection);
    SetColor(15);

    if (optionSelection == 1) { /// Create New Map

        SetColor(10);
        printf("Option 1 Selected. Please Wait While We Prepare Your Workspace...\n");
        SetColor(15);
        Sleep(1000);

        /// Reset Console
        system("cls");
        EditingMode_Header();

        /// Get Matrix Size
        printf("Enter Size Of The Map (Maximum Visual Support: 9): ");
        SetColor(3);
        scanf("%d", &mapSize);
        SetColor(15);

        /// Create & Initialize All Blocks To NORMAL
        Blocks blockMatrix1[mapSize][mapSize];
        for (int i = 0; i < mapSize; i++)
            for (int j = 0; j < mapSize; j++)
                blockMatrix1[i][j] = 4;

        EditMap(mapSize, blockMatrix1);

    } else if (optionSelection == 2) {  /// Generate Map

        SetColor(10);
        printf("Option 2 Selected. Please Wait While We Prepare Your Workspace...\n");
        SetColor(15);
        Sleep(1000);

        /// Reset Console
        system("cls");
        EditingMode_Header();

        /// Get Matrix Size
        printf("Enter Size Of The Map (Maximum Visual Support: 9): ");
        SetColor(3);
        scanf("%d", &mapSize);
        SetColor(15);

        Blocks blockMatrix[mapSize][mapSize];

        generate(mapSize, blockMatrix);
        printf("\n");
        showVisualMap(mapSize, blockMatrix);
        EditMap(mapSize, blockMatrix);

    } else if (optionSelection == 3) {  /// Edit Existing Map

        char *path;
        printf("Enter Path Of The Binary File: ");
        SetColor(3);
        scanf("%s", path);

        SetColor(10);
        printf("Option 3 Selected. Please Wait While We Prepare Your Workspace...\n");
        SetColor(15);
        Sleep(1000);

        FILE *MAP; /// Open File Handler

        /// Error Handler
        if ((MAP = fopen(path, "rb")) == NULL) {
            SetColor(12);
            printf("An Error Occurred While Saving/Opening The Binary File.\n");
            exit(-1);
        }

        /// Read & Save Data
        fread(&mapSize, sizeof(unsigned int), 1, MAP);

        Blocks blockMatrix2[mapSize][mapSize];
        unsigned char saveMap[mapSize][mapSize];
        for (int i = 0; i < mapSize; i++)
            for (int j = 0; j < mapSize; j++) {
                fread(&saveMap[i][j], sizeof(unsigned char), 1, MAP);

                switch(saveMap[i][j]) {
                    case '1': blockMatrix2[i][j] = 1; break;
                    case '2': blockMatrix2[i][j] = 2; break;
                    case '3': blockMatrix2[i][j] = 3; break;
                    case '4': blockMatrix2[i][j] = 4; break;
                }
            }

        fclose(MAP);
        EditMap(mapSize, blockMatrix2);
    } else if (optionSelection == 4) {  /// Exit
        exit(0);
    } else {    /// Event Handler
        SetColor(12);
        printf("Your Option Selection Is Invalid, Try Again.");
        goto z;
    }

    SetColor(7);
    return 0;
}

/// Function: Edit Map
void EditMap(int mapSize, Blocks blockMatrix[][mapSize]) {

    /// Reset Console
    system("cls");
    EditingMode_Header();

    /// Show Visual Map
    showVisualMap(mapSize, blockMatrix);

    FILE *MAP; /// Open File Handler
    int Xcoordinate, Ycoordinate, optionSelection;
    char blockType[20];
    char path[50];

    while (true) {

        system("cls");
        EditingMode_Header();

        /// Show Visual Map
        showVisualMap(mapSize, blockMatrix);

        unsigned char saveMap[mapSize][mapSize];

        SetColor(6);
        printf("\nCommands:\n1) Edit Cell\n2) Save & Exit\n3) Exit Without Saving\n\n");
        z:;
        SetColor(15);
        printf("Option Selection: ");
        SetColor(3);
        scanf("%d", &optionSelection);
        switch (optionSelection) {
            case 1:
                SetColor(15);
                printf("Enter Cell Coordinates: ");
                SetColor(3);
                scanf("%d%d", &Xcoordinate, &Ycoordinate);
                SetColor(15);
                printf("Enter Block Type To Set (");
                SetColor(5);
                printf("Energy");
                SetColor(15);
                printf("/");
                SetColor(9);
                printf("Mitosis");
                SetColor(15);
                printf("/");
                SetColor(4);
                printf("Forbidden");
                SetColor(15);
                printf("/");
                SetColor(7);
                printf("Normal");
                SetColor(15);
                printf("): ");
                SetColor(3);
                scanf("%s", blockType);

                if (strcasecmp("Energy", blockType) == 0)
                    blockMatrix[Xcoordinate][Ycoordinate] = 1;
                else if (strcasecmp("Mitosis", blockType) == 0)
                    blockMatrix[Xcoordinate][Ycoordinate] = 2;
                else if (strcasecmp("Forbidden", blockType) == 0)
                    blockMatrix[Xcoordinate][Ycoordinate] = 3;
                else if (strcasecmp("Normal", blockType) == 0)
                    blockMatrix[Xcoordinate][Ycoordinate] = 4;
                else {
                    SetColor(12);
                    printf("Your Option Selection Is Invalid, Try Again.\n\n");
                    Sleep(500);
                    goto z;
                }
            break;
            case 2:

                SetColor(15);
                printf("Enter Path To Save The Binary File: ");
                SetColor(3);
                scanf("%s", path);

                /// Error Handler
                if ((MAP = fopen(path, "wb")) == NULL) {
                    SetColor(12);
                    printf("An Error Occurred While Saving/Opening The Binary File.\n");
                    exit(-1);
                }

                /// Write Block Data To File
                fwrite(&mapSize, sizeof(unsigned int), 1, MAP);
                for (int i = 0; i < mapSize; i++)
                    for (int j = 0; j < mapSize; j++) {

                        switch(blockMatrix[i][j]) {
                            case 1: saveMap[i][j] = '1'; break;
                            case 2: saveMap[i][j] = '2'; break;
                            case 3: saveMap[i][j] = '3'; break;
                            case 4: saveMap[i][j] = '4'; break;
                        }

                        fwrite(&saveMap[i][j], sizeof(unsigned char), 1, MAP);
                    }

                fclose(MAP); /// Close FILE Handler

                open();

                SetColor(10);
                printf("Map Saved Successfully as %s.\n", path);
                SetColor(15);
                exit(0);
            break;
            case 3:
                return;
            break;
            default:
                SetColor(12);
                printf("Your Option Selection Is Invalid, Try Again.");
                SetColor(15);
            break;
        }
    }
}

/// Function: Make, Initialize & Show Visual Matrix With The Given Size On Runtime (Dynamic)
void showVisualMap(int mapSize, Blocks blockMatrix[][mapSize]) {

    int counter = 0;
    showHorizontalRuler(mapSize);

    /// Top Layer
    SetColor(14);
    printf("\t┃  ");
    for (int i = 0; i < mapSize; i++) {
        setCellColor(mapSize, 0, i, blockMatrix);
        if (i == 0)
            printf(" ━━━");
        else if (i % 2 == 0)
            printf("       ━━━");
    }
    SetColor(14);
    printf("\n %d\t┃  ", counter);

    for (int i = 0; i < mapSize; i++) {

        /// First Layer
        for (int j = 0; j < mapSize; j++) {
            setCellColor(mapSize, i, j, blockMatrix);
            if (j % 2 == 0)
                printf("┃ # ┃");
            else
                printf(" ━━━ ");
        }
        SetColor(14);
        printf("\n %d\t┃  ", counter);

        /// Second Layer
        for (int j = 0; j < mapSize; j++) {
            setCellColor(mapSize, i, j, blockMatrix);
            if (j % 2 == 0)
                printf(" ━━━ ");
            else
                printf("┃ # ┃");
        }
        SetColor(14);
        printf("\n\t┃  ");

        /// Third Layer
        for (int j = 0; j < mapSize; j++) {

            if ( i != mapSize - 1) {
                if (j % 2 == 0)
                    setCellColor(mapSize, i + 1, j, blockMatrix);
                else
                    setCellColor(mapSize, i, j, blockMatrix);

                printf(" ━━━ ");
            } else {
                setCellColor(mapSize, i, j, blockMatrix);
                if (j % 2 == 1)
                    printf(" ━━━ ");
                else
                    printf("     ");
            }
        }
        if (i != mapSize - 1) {
            SetColor(14);
            printf("\n %d\t┃  ", ++counter);
        }
        else
            printf("\n    ");
    }
}

/// Function: Show Horizontal Ruler
void showHorizontalRuler(int index) {
    SetColor(14);
    printf("\t┃  ");
    for (int i = 0; i < index * 5; i++) {
        if (i % 5 == 2)
            printf("%d", (i / 5));
        else
            printf(" ");
    }
    printf("\n");
    for (int i = 0; i < index * 8; i++)
        if (i != 8)
            printf("━");
        else
            printf(" ");
    printf("\n");
}

/// Function: Create New Map Header
void EditingMode_Header() {
    SetColor(9);
    printf("-------------------------------------- Map Editor Version 2.4 - Editing Mode --------------------------------------\n\n");
    SetColor(15);
}

/// Function: Set Color For Output
void SetColor(int ForgC) {

 	WORD wColor;
  	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  	CONSOLE_SCREEN_BUFFER_INFO csbi;

    /// We use 'csbi' for the wAttributes word - /Mask out all but the background attribute, and add in the foreground color
 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
      	SetConsoleTextAttribute(hStdOut, (csbi.wAttributes & 0xF0) + (ForgC & 0x0F));
}

/// Function: Set Cell Color
void setCellColor(int mapSize, int i, int j, Blocks blockMatrix[][mapSize]) {
    switch(blockMatrix[i][j]) {
        case 1: SetColor(2); break;
        case 2: SetColor(9); break;
        case 3: SetColor(4); break;
        case 4: SetColor(8); break;
    }
}
