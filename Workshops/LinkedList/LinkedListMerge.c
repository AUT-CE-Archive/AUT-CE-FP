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

List* merge(List *list1, List *list2) {

    /// Copy Lists
    Node *current1 = list1 -> root;
    Node *current2 = list2 -> root;

    /// Create New List
    List *list3 = createList();

    /// Comparison-Insertion
    while (current1 != NULL && current2 != NULL) {
        if (current1 -> value < current2 -> value) {
            addLast(list3, current1 -> value);
            current1 = current1 -> next;
        } else {
            addLast(list3, current2 -> value);
            current2 = current2 -> next;
        }
    }

    /// Copy The Rest Of The List1 To list3
    while (current1 != NULL) {
        addLast(list3, current1 -> value);
        current1 = current1 -> next;
    }

    /// Copy The Rest Of The List2 To list3
    while (current2 != NULL) {
        addLast(list3, current2 -> value);
        current2 = current2 -> next;
    }

    return list3;
}

void traverse(List *list) {

    Node *current = list -> root;

    while (current != NULL) {
        printf("%d ", current -> value);
        current = current -> next;
    }
}

int main() {

    List *list1 = createList();
    List *list2 = createList();
    List *list3 = createList();

    /// Fill List 1
    while (true) {
        int value;
        scanf("%d", &value);

        if (value != 0) addLast(list1, value);  /// Add To First List
        else break;
    }

    /// Fill List 2
    while (true) {
        int value;
        scanf("%d", &value);

        if (value != 0) addLast(list2, value);  /// Add To Second List
        else break;
    }

    list3 = merge(list1, list2);
    traverse(list3);

    return 0;
}
