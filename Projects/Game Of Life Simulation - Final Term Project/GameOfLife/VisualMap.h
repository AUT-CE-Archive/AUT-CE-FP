#ifndef VISUALMAP_H_INCLUDED
#define VISUALMAP_H_INCLUDED

/// Function: Make, Initialize & Show Visual Matrix With The Given Size On Runtime (Dynamic)
void showVisualMap(int mapSize, Blocks blockMatrix[][mapSize], List *list) {

    int counter = 0, step = 0;

    /// Create & Initialize A Character Matrix
    char Matrixmap[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++)
            Matrixmap[i][j] = " ";

    /// Convert LinkedList To Character Matrix
    Cell *current = list -> root;
    while (current != NULL) {
        Matrixmap[current -> x][current -> y] = current -> symbol;
        current = current -> next;
    }

    /// Create & Initialize An Character Array
    char ArrayMap[mapSize * mapSize];
    for (int i = 0; i < mapSize * mapSize; i++)
        ArrayMap[i] = " ";

    /// Convert Character Matrix To Character Array
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++)
            ArrayMap[step++] = Matrixmap[i][j];

    /// Counter For Drawing
    int upStep = 0, downStep = 1;

    /// Draw Horizontal Ruler
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

    /// Recursion
    for (int i = 0; i < mapSize; i++) {

        /// First Layer
        for (int j = 0; j < mapSize; j++) {
            setCellColor(mapSize, i, j, blockMatrix);
            if (j % 2 == 0) {
                if (ArrayMap[upStep] == 'X' || ArrayMap[upStep] == 'O')
                    printf("┃ %c ┃", ArrayMap[upStep]);
                else
                    printf("┃   ┃");

                if (j != mapSize - 1)
                    upStep += 2;
                else
                    upStep += 1;
            }
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
            else {
                if (ArrayMap[downStep] == 'X' || ArrayMap[downStep] == 'O')
                    printf("┃ %c ┃", ArrayMap[downStep]);
                else
                    printf("┃   ┃");

                if (j != mapSize - 2)
                    downStep += 2;
                else
                    downStep += 3;
            }
        }
        SetColor(14);
        printf("\n\t┃  ");

        /// Third Layer
        for (int j = 0; j < mapSize; j++) {

            if (j % 2 == 1)
                setCellColor(mapSize, i, j, blockMatrix);
            else
                setCellColor(mapSize, i + 1, j, blockMatrix);

            if (i != mapSize - 1)
                printf(" ━━━ ");
            else {
                if (i == mapSize - 1 && j % 2 == 1)
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
    printf("\n");

    SetColor(15);
    printf(" / ");
    SetColor(2);
    printf("ENERGY");
    SetColor(15);
    printf(" / ");
    SetColor(9);
    printf("MITOSIS");
    SetColor(15);
    printf(" / ");
    SetColor(4);
    printf("FORBIDDEN");
    SetColor(15);
    printf(" / ");
    SetColor(8);
    printf("NORMAL");
    SetColor(15);
    printf(" / \n");
}

#endif // VISUALMAP_H_INCLUDED
