///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

#ifndef MAPGENERATOR_H_INCLUDED
#define MAPGENERATOR_H_INCLUDED

typedef enum Blocks {
    ENERGY = 1,     /// Cell Code Color:    5
    MITOSIS = 2,     /// Cell Code Color:   9
    FORBIDDEN = 3,     /// Cell Code Color: 4
    NORMAL = 4,     /// Cell Code Color:    7
} Blocks;

/// Function: Generate A Balanced Map Containing All Four Cell Blocks With
void generate(int mapSize, Blocks blockMatrix[][mapSize]) {

    int energyBlocksCount = ceil(0.1 * pow(mapSize, 2));      /// 10%
    int mitosisBlocksCount = ceil(0.1 * pow(mapSize, 2));     /// 10%
    int forbiddenBlocksCount = ceil(0.2 * pow(mapSize, 2));   /// 20%
    int normalBlocksCount;                                    /// 60% (Rest)

    /// Reset Matrix
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++)
            blockMatrix[i][j] = 4;  /// NORMAL By Default

    generateEnergyBlocks(energyBlocksCount, mapSize, blockMatrix);
    generateMitosisBlocks(mitosisBlocksCount, mapSize, blockMatrix);
    generateForbiddenBlocks(forbiddenBlocksCount, mapSize, blockMatrix);
}

/// Function: Check Exists For Any Duplicate X, Y Coordinates
bool checkCoordinateExist(int x, int y, int mapSize, Blocks blockMatrix[][mapSize]) {
    if (blockMatrix[x][y] != 4)
        return true;

    return false;
}

/// Function: Generate Energy Blocks
void generateEnergyBlocks(int count, int mapSize, Blocks blockMatrix[][mapSize]) {

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        while (true) {
            int x = rand() % mapSize;
            int y = rand() % mapSize;

            if (!checkCoordinateExist(x, y, mapSize, blockMatrix)) {
                blockMatrix[x][y] = 1;
                break;
            }
        }
    }
}

/// Function: Generate Mitosis Blocks
void generateMitosisBlocks(int count, int mapSize, Blocks blockMatrix[][mapSize]) {

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        while (true) {
            int x = rand() % mapSize;
            int y = rand() % mapSize;

            if (!checkCoordinateExist(x, y, mapSize, blockMatrix)) {
                blockMatrix[x][y] = 2;
                break;
            }
        }
    }
}

/// Function: Generate Forbidden Blocks
void generateForbiddenBlocks(int count, int mapSize, Blocks blockMatrix[][mapSize]) {

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        while (true) {
            int x = rand() % mapSize;
            int y = rand() % mapSize;

            if (!checkCoordinateExist(x, y, mapSize, blockMatrix)) {
                blockMatrix[x][y] = 3;
                break;
            }
        }
    }
}

#endif // MAPGENERATOR_H_INCLUDED
