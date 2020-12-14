///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

#ifndef LOAD&SAVE_H_INCLUDED
#define LOAD&SAVE_H_INCLUDED

void save(int mapSize, List *list, int resourceMap[][mapSize], char *gameMode, Blocks blockMatrix[][mapSize], bool againstAI) {

    /// Save Map
    saveMap("map.bin", mapSize, blockMatrix);

    /// Save Game
    saveGame("gameSave.bin", mapSize, list, resourceMap, gameMode, againstAI);
}

void saveMap(char *path, int mapSize, Blocks blockMatrix[][mapSize]) {

    FILE *File;

    /// Error Handler
    if ((File = fopen(path, "wb")) == NULL) {
        SetColor(12);
        printf("An Error Occurred While Saving The Binary File.\n");
        exit(-1);
    }

    /// Write Map Size Into Binary
    fwrite(&mapSize, sizeof(unsigned int), 1, File);

    unsigned char saveMap[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++) {

            switch(blockMatrix[i][j]) {
                case 1: saveMap[i][j] = '1'; break;
                case 2: saveMap[i][j] = '2'; break;
                case 3: saveMap[i][j] = '3'; break;
                case 4: saveMap[i][j] = '4'; break;
            }

            fwrite(&saveMap[i][j], sizeof(unsigned char), 1, File);
        }

    fclose(File);
}

void load() {

    /* ----------------------------------- MAP ---------------------------------- */
    FILE *MAP; /// Open File Handler
    int mapSize;

    /// Error Handler
    if ((MAP = fopen("map1.bin", "rb")) == NULL) {
        SetColor(12);
        printf("An Error Occurred While Loading The Binary File \"map1.bin\".\n");
        exit(-1);
    }

    /// Read Map Size
    fread(&mapSize, sizeof(unsigned int), 1, MAP);

    unsigned char saveMap[mapSize][mapSize];
    Blocks blockMatrix[mapSize][mapSize];

    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            fread(&saveMap[i][j], sizeof(unsigned char), 1, MAP);

            switch(saveMap[i][j]) {
                case '1': blockMatrix[i][j] = 1; break;
                case '2': blockMatrix[i][j] = 2; break;
                case '3': blockMatrix[i][j] = 3; break;
                case '4': blockMatrix[i][j] = 4; break;
            }
        }
    }

    fclose(MAP);

    /* ----------------------------------- GAME ---------------------------------- */
    FILE *Game;

    /// Error Handler
    if ((Game = fopen("gameSave.bin", "rb")) == NULL) {
        SetColor(12);
        printf("An Error Occurred While Reading The Binary File \"gameSave.bin\".\n");
        exit(-1);
    }

    /// Write The Number Of Cells
    int cellCount;
    fread(&cellCount, sizeof(int), 1, Game);

    /// Create List
    List *list = createList();

    /// Read The Cells Properties
    for (int i = 0; i < cellCount; i++) {

        char symbol;
        int x, y, score, energy;

        fread(&symbol, sizeof(char), 1, Game);
        fread(&x, sizeof(int), 1, Game);
        fread(&y, sizeof(int), 1, Game);
        fread(&score, sizeof(int), 1, Game);
        fread(&energy, sizeof(int), 1, Game);

        Cell *cell = createCell(x, y, symbol, score, energy, mapSize, list, blockMatrix);
        addLast(list, cell);
    }

    /// Read Map Size
    fread(&mapSize, sizeof(int), 1, Game);

    /// Read Resource Map
    int resourceMap[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++)
            fread(&resourceMap[i][j], sizeof(int), 1, Game);

    /// Read Game Mode
    int gameModeID;
    fread(&gameModeID, sizeof(int), 1, Game);

    fclose(Game);

    /// Let's Play!
    switch(gameModeID) {
        case 0: play(mapSize, blockMatrix, list, resourceMap, "SinglePlayer", false); break;
        case 1: play(mapSize, blockMatrix, list, resourceMap, "MultiPlayer", true); break;
        case 2: play(mapSize, blockMatrix, list, resourceMap, "MultiPlayer", true); break;
    }
}

void saveGame(char *path, int mapSize, List *list, int resourceMap[][mapSize], char* gameMode, bool againstAI) {

    FILE *Game;

    /// Error Handler
    if ((Game = fopen(path, "wb")) == NULL) {
        SetColor(12);
        printf("An Error Occurred While Saving The Binary File \"gameSave.bin\".\n");
        exit(-1);
    }

    /// Calculate The Number Of Cells
    int cellCount = 0;
    Cell *current = list -> root;
    while (current != NULL) {
        cellCount++;
        current = current -> next;
    }

    /// Write The Number Of Cells
    fwrite(&cellCount, sizeof(int), 1, Game);

    /// Write The Cells Properties
    current = list -> root;
    while (current != NULL) {

        char symbol = current -> symbol;
        int x = current -> x;
        int y = current ->  y;
        int score = current -> score;
        int energy = current -> energy;

        fwrite(&symbol, sizeof(char), 1, Game);
        fwrite(&x, sizeof(int), 1, Game);
        fwrite(&y, sizeof(int), 1, Game);
        fwrite(&score, sizeof(int), 1, Game);
        fwrite(&energy, sizeof(int), 1, Game);

        current = current -> next;
    }

    /// Write Map Size
    fwrite(&mapSize, sizeof(int), 1, Game);

    /// Write Resource Map
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++)
            fwrite(&resourceMap[i][j], sizeof(int), 1, Game);

    /// Write Game Mode
    int gameModeID;
    if (strcmp(gameMode, "SinglePlayer") == 0 && !againstAI)
        gameModeID = 0;
    else if (strcmp(gameMode, "MultiPlayer") == 0 && !againstAI)
        gameModeID = 1;
    else if (strcmp(gameMode, "MultiPlayer") == 0 && againstAI)
        gameModeID = 2;
    fwrite(&gameModeID, sizeof(int), 1, Game);

    fclose(Game);
}

#endif // LOAD&SAVE_H_INCLUDED
