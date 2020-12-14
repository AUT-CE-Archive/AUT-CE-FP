///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

/// Main Functions
void showHorizontalRuler(int index);
void showVisualMap(int mapSize, Blocks blockMatrix[][mapSize], List *list);
void loadingText(int selectionOption);

/// MapGenerator.h Functions
void generate(int mapSize, Blocks blockMatrix[][mapSize]);
bool checkCoordinateExist(int x, int y, int mapSize, Blocks blockMatrix[][mapSize]);
void generateEnergyBlocks(int count, int mapSize, Blocks blockMatrix[][mapSize]);
void generateMitosisBlocks(int count, int mapSize, Blocks blockMatrix[][mapSize]);
void generateForbiddenBlocks(int count, int mapSize, Blocks blockMatrix[][mapSize]);

/// Headers.h Functions
void GameOfLife_Header(void);
void SinglePlayer_Header(void);
void MultiPlayer_header(void);

/// Color.h Functions
void SetColor(int ForgC);
void setCellColor(int mapSize, int i, int j, Blocks blockMatrix[][mapSize]);

/// LinkedList.h Functions
void addLast(List *list, Cell *cell);
void createCells(int count, int mapSize, Blocks blockMatrix[][mapSize], List *list, char symbol);
bool canIMove(List *list, int x, int y, int mapSize, Blocks blockMatrix[][mapSize]);
List* createList();
Cell* createCell(char symbol, int score, int mapSize, List *list, Blocks blockMatrix[][mapSize]);

/// Game.h Functions
void play(int mapSize, Blocks blockMatrix[][mapSize], List *list, int resourceMatrix[][mapSize], char *gameMode)
void resetConsole(char *gameMode);
bool checkExist(List *list, int x, int y);
void initializeEnergyBlocks(int mapSize, Blocks blockMatrix[][mapSize], int resourceMatrix[][mapSize]);
void play(int mapSize, Blocks blockMatrix[][mapSize], List *list, int resourceMatrix[][mapSize], char *gameMode);
bool canCellMove(int toX, int toY, int mapSize, Blocks blockMatrix[][mapSize], List *list);
void save(int mapSize, List *list, int resouceMatrix[][mapSize], char* gameMode);
void showHiddenMap(int mapSize, Blocks blockMatrix[][mapSize], int resouceMatrix[][mapSize], List *list);

/// Load&Save.h Functions
void save(int mapSize, List *list, int resourceMap[][mapSize], char *gameMode, Blocks blockMatrix[][mapSize], bool againstAI);
void saveMap(char *path, int mapSize, Blocks blockMatrix[][mapSize]);
void saveGame(char *path, int mapSize, List *list, int resourceMap[][mapSize], char* gameMode, bool againstAI);
void load();

#endif // INTERFACE_H_INCLUDED
