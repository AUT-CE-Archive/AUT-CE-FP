///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

/// C & C++ Standard Libraries
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <math.h>

/// Alternative Headers
#include "color.h"
#include "headers.h"
#include "LinkedList.h"
#include "Game.h"
#include "MapGenerator.h"
#include "Load&Save.h"
#include "VisualMap.h"

int main() {

    int optionSelection;

    SetConsoleTitle("Game Of Life - Developed By: Keivan Ipchi Hagh");
    GameOfLife_Header();

    SetColor(6);
    printf("Setting Up Console: ");
    system("chcp 65001");
    printf("UTF-8 Encoding Set.\n\n");

    SetColor(15);
    printf("Choose An Action To Continue:\n\n1) Load Last Saved Game\n2) New Single Player Game\n3) New MultiPlayer Game (Against AI)\n4) New MultiPlayer Game\n5) Exit");
    z:;
    SetColor(15);
    printf("\n\nOption Selection [1-4]: ");
    SetColor(3);
    scanf("%d", &optionSelection);

    if (optionSelection == 1) {  /// Load Game

        load();

    } else if (optionSelection == 2) {  /// Single Player Game

        loadingText(2);

        /// Reset Console
        system("cls");
        SinglePlayer_Header();

        int mapSize, cellCount;
        List *list = createList();  /// Create Player Cell List

        SetColor(15);
        printf("Enter Size Of The Map (Maximum Visual Support: 9): ");
        SetColor(3);
        scanf("%d", &mapSize);
        SetColor(15);
        printf("Enter Number Of Cells: ");
        SetColor(3);
        scanf("%d", &cellCount);

        /// Create & Initialize All Blocks To Random[0-4]
        srand(time(NULL));
        Blocks blockMatrix[mapSize][mapSize];
        generate(mapSize, blockMatrix);

        /// Create, Initialize And Add Cells To The List
        createCells(cellCount, mapSize, blockMatrix, list, 'X');

        int resourceMatrix[mapSize][mapSize];
        for (int i = 0; i < mapSize; i++)
            for (int j = 0; j < mapSize; j++)
                resourceMatrix[i][j] = -1;

        /// Reset Console
        system("cls");
        SinglePlayer_Header();

        /// Let's Play!!!
        initializeEnergyBlocks(mapSize, blockMatrix, resourceMatrix);
        play(mapSize, blockMatrix, list, resourceMatrix, "SinglePlayer", false);

    } else if (optionSelection == 4 || optionSelection == 3) {  /// Multi Player Game

        loadingText(3);

        /// Reset Console
        system("cls");
        MultiPlayer_header();

        int mapSize, cellCount1, cellCount2;
        List *list = createList();  /// Create Player Cell List

        SetColor(15);
        printf("Enter Size Of The Map (Maximum Visual Support: 9): ");
        SetColor(3);
        scanf("%d", &mapSize);
        SetColor(15);
        printf("Enter Number Of Cells For Player 1: ");
        SetColor(3);
        scanf("%d", &cellCount1);
        SetColor(15);
        printf("Enter Number Of Cells For Player 2: ");
        SetColor(3);
        scanf("%d", &cellCount2);

        /// Create & Initialize All Blocks To Random[0-4]
        srand(time(NULL));
        Blocks blockMatrix[mapSize][mapSize];
        generate(mapSize, blockMatrix);

        /// Create, Initialize And Add Cells To The List For Player 1
        createCells(cellCount1, mapSize, blockMatrix, list, 'X');

        /// Create, Initialize And Add Cells To The List For Player 2
        createCells(cellCount2, mapSize, blockMatrix, list, 'O');

        int resourceMatrix[mapSize][mapSize];
        for (int i = 0; i < mapSize; i++)
            for (int j = 0; j < mapSize; j++)
                resourceMatrix[i][j] = -1;

        /// Reset Console
        system("cls");
        MultiPlayer_header();

        /// Let's Play!!!
        if (optionSelection == 4) {
            initializeEnergyBlocks(mapSize, blockMatrix, resourceMatrix);
            play(mapSize, blockMatrix, list, resourceMatrix, "MultiPlayer", true);
        }
        else {
            play(mapSize, blockMatrix, list, resourceMatrix, "MultiPlayer", false);
        }

    } else if (optionSelection == 5) {  /// Exit

        SetColor(7);
        exit(0);

    } else {
        SetColor(12);
        printf("In Which Universe Is '%d' Between 1 & 5??? Try Again.");
        goto z;
    }

    SetColor(7);
    return 0;
}

/// Function: Show Loading text
void loadingText(int selectionIndex) {
    SetColor(10);
    printf("Option %d Selected. Hold On While We Prepare Your Workspace...\n", selectionIndex);
    SetColor(15);
    Sleep(1000);
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
    printf("━━━━━━━━━━━━━━━━━━");
    for (int i = 0; i < index; i++)
        if (i != 8)
            printf("━━━━━");
        else
            printf("    ");
    printf("\n");
}
