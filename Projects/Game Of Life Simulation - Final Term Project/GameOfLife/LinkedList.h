///*********************************************************///
///     Developed By:   Keivan Ipchi Hagh                   ///
///     Student Number: 9831073                             ///
///     Due Date:       Thursday, January 23, 2020          ///
///     Course:         Fundamentals Of Programming In C    ///
///     Project Name:   Game Of Life                        ///
///*********************************************************///

//#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct Cell {
    char symbol;
    int x, y;
    int score;
    int energy;
    struct Cell *next;
} Cell;

typedef struct List {
    Cell *root;
} List;

/// Check Exist Function
bool canIMove(List *list, int x, int y, int mapSize, Blocks blockMatrix[][mapSize]) {
    Cell *current = list -> root;

    while (current != NULL) {
        if ((current -> x == x && current -> y == y) || (blockMatrix[x][y] == FORBIDDEN))
            return true;
        current = current -> next;
    }
    return false;
}

/// Create List & Point To Root
List* createList() {
    List *list = (List*)malloc(sizeof(List));
    list -> root = NULL;
    return list;
}

/// Create & Initialize New Cell
Cell* createCell(int x, int y, char symbol, int score, int energyLVL, int mapSize, List *list, Blocks blockMatrix[][mapSize]) {
    /// Create New Cell & Allocate Memory To It
    Cell *cell = (Cell*)malloc(sizeof(Cell));

    cell -> symbol = symbol;
    cell -> score = score;
    cell -> next = NULL;
    cell -> energy = energyLVL;
    cell -> x = x;
    cell -> y = y;

    /// Random X, Y If Not Initialized Before Hand
    srand(time(NULL));
    while (x == -1 && y == -1) {
        int x = rand() % mapSize;
        int y = rand() % mapSize;

        if (!canIMove(list, x, y, mapSize, blockMatrix)) {
            cell -> x = x;
            cell -> y = y;
            break;
        }
    }
    return cell;
}

/// Function: Add Cell To The End Of List
void addLast(List *list, Cell *cell) {

    /// Create New Node & Allocate Memory To It
    Cell *node = cell;

    /// What If Root Is NULL???!
    if (list -> root == NULL) {
        list -> root = node;
        return;
    }

    /// Make A Copy
    Cell *current = list -> root;

    /// Iterate
    while (current -> next != NULL)
        current = current -> next;

    /// Re-Direct pointer
    current -> next = node;
}

/// Function: Create Cells
void createCells(int count, int mapSize, Blocks blockMatrix[][mapSize], List *list, char symbol) {
    for (int i = 0; i < count; i++) {
        Cell *cell = createCell(-1, -1, symbol, 0, 0, mapSize, list, blockMatrix); /// Create & Initialize Cell
        addLast(list, cell);
    }
}
