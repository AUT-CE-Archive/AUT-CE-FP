#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// Developed By: Keivan Ipchi Hagh - All Rights Reserved ///

/// Create & Rename Structs
typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    int length;
    Node *root;
} List;

/// Create List & Point To Root
List* createList() {
    List *list = (List*)malloc(sizeof(List));
    list -> length = 0;
    list -> root = NULL;
    return list;
}

Node* createNode(int value) {
    /// Create New Node & Allocate Memory To It
    Node *node = (Node*)malloc(sizeof(Node));
    node -> value = value;
    node -> next = NULL;
    return node;
}

void addLast(List *list, int value) {

    /// Create New Node & Allocate Memory To It
    Node *node = createNode(value);

    /// Increase Length
    list -> length++;

    /// What If Root Is NULL???!
    if (list -> root == NULL) {
        list -> root = node;
        return;
    }

    /// Make A Copy
    Node *current = list -> root;

    /// Iterate
    while (current -> next != NULL)
        current = current -> next;

    /// Re-Direct pointer
    current -> next = node;
}

void traverse(List *list) {

    Node *current = list -> root;

    while (current != NULL) {
        printf("%d ", current -> value);
        current = current -> next;
    }
}

List* switchElements(List *list) {

    /// Make A Copy
    Node *current = list -> root;

    /// Make A New list
    List *newList = createList();

    int counter = 0;    /// IDK Why, But It Works. So Let's Keep It That Way (:

    while (counter < list -> length - 1 && current -> next -> next != NULL) {

        /// Add To The New List Reversed
        addLast(newList, current -> next -> value);
        addLast(newList, current -> value);

        /// Step
        current = current -> next -> next;
        counter += 2;
    }

    /// If Length Is Odd, Add The Last Node To The New List
    if (list -> length % 2 == 1) {
        current = list -> root; /// Re-Assign Current
        while (current -> next != NULL) /// Iterate To The Last Node
            current = current -> next;  /// Step

        addLast(newList, current -> value);
    } else {
        current = list -> root; /// Re-Assign Current
        while (current -> next -> next != NULL) /// Iterate To The Last Node
            current = current -> next;  /// Step

        /// Add Last Two Nodes To The New List Reversed
        addLast(newList, current -> next -> value);
        addLast(newList, current -> value);
    }

    return newList;
}

int main() {

    List *list = createList();

    /// Fill List
    while (true) {
        int value;
        scanf("%d", &value);

        if (value != 0) addLast(list, value);  /// Add To The List
        else break;
    }

    List *newList = switchElements(list);
    traverse(newList);

    return 0;
}
