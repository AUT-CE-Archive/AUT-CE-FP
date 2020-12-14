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

bool isPalindrome(List *list, int index) {

    Node *current1 = list -> root;
    Node *current2 = list -> root;
    int cnt1 = 0;
    int cnt2 = 0;

    /// Iterate From Beginning
    while (cnt1 < index && current1 -> next != NULL) {
        current1 = current1 -> next;
        cnt1++;
    }

    /// Iterate From The End
    while (cnt2 < list -> length - index - 1) {
        current2 = current2 -> next;
        cnt2++;
    }

    /// Check
    if (current1 -> value == current2 -> value)
        return true;
    else
        return false;
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

    int index = 0;
    while (index < list -> length / 2) {
        bool stats = isPalindrome(list, index);

        if (stats == false) {
            printf("false");
            return 0;
        }
        index++;
    }
    printf("true");

    return 0;
}
