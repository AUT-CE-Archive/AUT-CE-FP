///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/// Main Game Engine
/// Supports SinglePlayer/ MultiPlayer/ MultiPlayer AI

/// Function: Reset Console
void resetConsole(char *gameMode) {
    /// Reset Console
    system("cls");
    if (strcmp(gameMode, "SinglePlayer") == 0)
        SinglePlayer_Header();
    else
        MultiPlayer_header();
}

/// Function: Check Exist For Cell Using X, Y Properties
bool checkExist(List *list, int x, int y) {
    Cell *current = list -> root;
    while (current != NULL) {
        if (current -> x == x && current -> y == y)
            return true;
        current = current -> next;
    }
    return false;
}

/// Checks If The Right Player Makes The Write Move
bool checkPlayersTurn(int playerStep, int x, int y, List *list) {

    Cell *current = list -> root;
    while (current != NULL) {

        if (current -> x == x && current -> y == y) {
            if (current -> symbol == 'X' && playerStep % 2 == 0)
                return true;
            else if (current -> symbol == 'O' && playerStep % 2 == 1)
                return true;
            else
                return false;
        }
        current = current -> next;
    }
    return false;
}

/// Function: initialize Energy Blocks With Initial 100 Points
void initializeEnergyBlocks(int mapSize, Blocks blockMatrix[][mapSize], int resourceMatrix[][mapSize]) {
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++)
            if (blockMatrix[i][j] == 1)
                resourceMatrix[i][j] = 100;
}

/// Function: Show ScoreBoard & Resource Map
void showHiddenMap(int mapSize, Blocks blockMatrix[][mapSize], int resouceMatrix[][mapSize], List *list) {

    resetConsole("SinglePlayer");

    /// Score Board
    SetColor(10);
    printf(" - SCORE BOARD\n");

    int playerOneScore = 0, playerTwoScore = 0;

    Cell *current = list -> root;
    while (current != NULL) {
        if (current -> symbol == 'X')
            playerOneScore += current -> score;
        else
            playerTwoScore += current -> score;
        current = current -> next;
    }

    SetColor(15);
    printf("\tPlayer 'X' Overall Score: ");
    SetColor(3);
    printf("%d", playerOneScore);

    SetColor(15);
    printf("\n\tPlayer 'O' Overall Score: ");
    SetColor(3);
    printf("%d", playerTwoScore);

    /// Resource Map
    SetColor(10);
    printf("\n\n - Resource Map\n");

    SetColor(15);
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            SetColor(10);
            printf("'");
            SetColor(3);
            if (resouceMatrix[i][j] >= 0)
                SetColor(12);
            printf("%d", resouceMatrix[i][j]);
            SetColor(10);
            printf("'\t");
        }
        printf("\n\n");
    }

    /// Ending
    SetColor(7);
    printf("\n\n\nPress Any Key To Continue...");
    getch();
}

/// Function: Main Play Function
void play(int mapSize, Blocks blockMatrix[][mapSize], List *list, int resourceMatrix[][mapSize], char *gameMode, bool againstAI) {

    int x, y, optionsSelection;
    int step = 0;   /// Against AI Counter

    resetConsole(gameMode);

    /// Show Visual Map
    showVisualMap(mapSize, blockMatrix, list);

    int playerStep = 0;

    /// Choose Action For Target Cell
    while(true) {

        /// First SAVE! (Auto Save)
        save(mapSize, list, resourceMatrix, gameMode, blockMatrix, againstAI);

        /// Get Target Cell Coordinates
        while(true) {
            SetColor(15);
            if (strcmp(gameMode, "SinglePlayer") == 0)
                printf("\nEnter Target Cell Coordinates: ");
            else {
                if (playerStep % 2 == 0)
                    printf("\nEnter Target Cell Coordinates For Player 'X': ");
                else
                    printf("\nEnter Target Cell Coordinates For Player 'O': ");
                playerStep++;
            }
            SetColor(3);
            scanf("%d %d", &x, &y);

            if (checkExist(list, x, y))
                if (checkPlayersTurn(playerStep, x, y, list))
                    break;
                else {
                    SetColor(12);
                    printf("Select You Own Block Smart ass! Not The Other Dude.\n");
                    playerStep--;
                    SetColor(15);
                }
            else {
                SetColor(12);
                printf("Don't You See There Is Nothing There??! Select Again.\n");
                playerStep--;
                SetColor(15);
            }
        }

        SetColor(15);
        printf("\nActions:\n1) Move\n2) Split Cell\n3) Boost Energy\n4) View Scoreboard & Resource Map\n5) Exit (Auto Save ON - gameSave.bin)");
        z:;
        printf("\n\nOption Selection[1-3]: ");
        SetColor(3);
        scanf("%d", &optionsSelection);

        /// Variables For Switch Statement
        Cell *current;

        switch(optionsSelection) {
            case 1: /// Move
                SetColor(15);
                printf("\nChoose Among The Directions:\n1) North\n2) South\n3) North-East\n4) North-West\n5) South-East\n6) South-West");
                t:;
                printf("\n\nOption Selection[1-6]: ");
                SetColor(3);
                scanf("%d", &optionsSelection);

                    switch(optionsSelection) {
                        case 1: move(x, y, x - 1, y, mapSize, blockMatrix, list); resetConsole(gameMode); break;
                        case 2: move(x, y, x + 1, y, mapSize, blockMatrix, list); resetConsole(gameMode); break;
                        case 3: move(x, y, x - 1, y + 1, mapSize, blockMatrix, list); resetConsole(gameMode); break;
                        case 4: move(x, y, x - 1, y - 1, mapSize, blockMatrix, list); resetConsole(gameMode); break;
                        case 5:
                            if (y % 2 == 0) {
                                move(x, y, x, y + 1, mapSize, blockMatrix, list); resetConsole(gameMode);
                            } else {
                                move(x, y, x + 1, y + 1, mapSize, blockMatrix, list); resetConsole(gameMode);
                            }
                            break;
                        case 6:
                            if (y % 2 == 0) {
                                move(x, y, x, y - 1, mapSize, blockMatrix, list); resetConsole(gameMode);
                            } else {
                                move(x, y, x + 1, y - 1, mapSize, blockMatrix, list); resetConsole(gameMode);
                            }
                            break;
                        default:
                            SetColor(12);
                            printf("In Which Universe Is '%d' Between 1 & 6?? HA?");
                            SetColor(15);
                            goto t;
                        break;
                    }
            break;
            case 2: /// Split

                current = list -> root;
                while (current != NULL) {
                    if (current -> x == x && current -> y == y && blockMatrix[x][y] == 2 && current -> energy >= 80) {

                        current -> energy = 40;
                        /// Create New Cell & Allocate Memory To It
                        Cell *cell = (Cell*)malloc(sizeof(Cell));

                        /// Initialize Random X, Y
                        srand(time(NULL));
                        while (true) {
                            int dirX = rand() % 3 - 1;
                            int dirY = rand() % 3 - 1;

                            if (!canIMove(list, x + dirX, y + dirY, mapSize, blockMatrix)) {
                                cell -> x = x + dirX;
                                cell -> y = y + dirY;
                                break;
                            }
                        }
                        cell -> symbol = current -> symbol;
                        cell -> score = 0;
                        cell -> next = NULL;
                        cell -> energy = 40;

                        /// Add To The List
                        addLast(list, cell);
                    } else {
                        SetColor(12);
                        printf("There Is Either Not Enough Energy To Split Or You Chose The Wrong Place /:\n");
                        Sleep(1500);
                        SetColor(15);
                        break;
                    }
                    current = current -> next;
                }

            break;

            case 3: /// Boost
                current = list -> root;
                while (current != NULL) {
                    if (current -> x == x && current -> y == y) {
                        if (resourceMatrix[x][y] >= 15) {

                            if (current -> energy <= 85) {
                                current -> energy += 15;
                                current -> score += 15;
                                resourceMatrix[x][y] -= 15;
                            } else {
                                SetColor(12);
                                printf("Dude, You Wanna Blow Up The Cell??? Can't Charge Anymore!\n");
                                Sleep(500);
                                SetColor(15);
                            }

                            SetColor(10);
                            printf("YEY! Cell Charged 15%% (%d%% Energy Remaining On (%d, %d))\n", resourceMatrix[x][y], x, y);
                            SetColor(15);
                            Sleep(1500);
                        } else if (resourceMatrix[x][y] >= 0) {

                            if (current -> energy <= 85) {
                                current -> energy += resourceMatrix[x][y];
                                resourceMatrix[x][y] = 0;
                            } else {
                                SetColor(12);
                                printf("Dude, You Wanna Blow Up The Cell??? Can't Charge Anymore!\n");
                                Sleep(500);
                                SetColor(15);
                            }

                            SetColor(10);
                            printf("YEY! Cell Charged %d%% (%d%% Energy Remaining On (%d, %d))\n", resourceMatrix[x][y], resourceMatrix[x][y], x, y);
                            SetColor(15);
                            Sleep(1500);
                        } else {
                            SetColor(12);
                            printf("Sry ): Not Enough Energy To Boost.\n");
                            Sleep(500);
                            SetColor(15);
                        }
                        break;
                    }
                    current = current -> next;
                }
            break;

            case 4: /// View Scoreboard & Resource Map
                showHiddenMap(mapSize, blockMatrix, resourceMatrix, list);
            break;

            case 5: /// Exit
                SetColor(7);
                exit(0);
            break;

            default:
                SetColor(12);
                printf("In Which Universe Is '%d' Between 1 & 5??? Try Again.", optionsSelection);
                SetColor(15);
                goto z;
            break;
        }

        /// Reset Console
        resetConsole(gameMode);

        showVisualMap(mapSize, blockMatrix, list);
    }
}

/// Function: Check If Cell Can Move To The Target Location
bool canCellMove(int toX, int toY, int mapSize, Blocks blockMatrix[][mapSize], List *list) {

    /// Check Out Of Map
    if (toX < 0 || toX >= mapSize)
        return false;
    if (toY < 0 || toY >= mapSize)
        return false;

    /// Check Forbidden Cell
    if (blockMatrix[toX][toY] == 3)
        return false;

    /// Check Other Cells For Same Coordinates
    Cell *current = list -> root;
    while (current != NULL) {
        if (current -> x == toX && current -> y == toY)
            return false;
        current = current -> next;
    }

    /// Otherwise
    return true;
}

/// Function: Takes Care Of The Entire Moving Exceptions & ...
void move(int fromX, int fromY, int toX, int toY, int mapSize, Blocks blockMatrix[][mapSize], List *list) {

    Cell *current = list -> root;

    while (current != NULL) {
        if (current -> x == fromX && current -> y == fromY) {
            if (canCellMove(toX, toY, mapSize, blockMatrix, list)) {
                current -> x = toX;
                current -> y = toY;
                break;
            } else {
                SetColor(12);
                printf("You Joking? Can't Move Down There /:");
                SetColor(15);
                Sleep(1000);
            }
        }
        current = current -> next;
    }

}

#endif // GAME_H_INCLUDED
