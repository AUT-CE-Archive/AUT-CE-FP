/// Standard C Libraries
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

/// Developed By: Keivan Ipchi Hagh - All Rights Reserved ///

/// Node Object
typedef struct Node {
    int value;
    struct Node *next;
} Node;

/// Function Declaration
Node* createNode();
void traverse(Node *root);
void addLast(Node *root, int value);
void addFirst(Node **root, int value);
void removeLast(Node *root);
void removeFirst(Node **root);
int getLength(Node *root);
void removeByValue(Node *root, Node **rootptr, int value);

/// Main Function
int main() {

    /// Create & Initialize Root Node
    Node *root = createNode();
    (*root).value = 10;
    (*root).next = NULL;

    addLast(root, 15);
    addLast(root, 20);
    addFirst(&root, 12);

    traverse(root);
    printf("\n");

    removeByValue(root, &root, 20);

    traverse(root);

    return 0;
}

/// Create Node Function
Node* createNode() {
    Node *node = (Node*)malloc(sizeof(Node));   /// Allocate Memory In Heap
    return node;
}

/// Traverse function
void traverse(Node *root) {
    Node *current = root;   /// Make A Copy

    while (current != NULL) {
        printf("%d ", (*current).value);
        current = (*current).next;
    }
}

/// Add Last Function
void addLast(Node *root, int value) {

    Node *current = root;   /// Make A Copy

    /// Iterate To The Last Known Node
    while ((*current).next != NULL)
        current = (*current).next;

    /// Create & Initialize New Node
    Node *node = createNode();
    (*node).value = value;
    (*node).next = NULL;

    /// Set Last Node
    (*current).next = node;
}

/// Add First Function
void addFirst(Node **root, int value) {

    /// Create & Initialize New Node
    Node *node = createNode();
    (*node).value = value;
    (*node).next = *root;
    *root = node;
}

/// Remove Last Function - Works Only If More Than One Node Exists!
void removeLast(Node *root) {

    /// Does Root Exist?
    if (root == NULL)
        return;

    Node *current = root;   /// Make A Copy

    while (current -> next -> next != NULL)
        current = (*current).next;

    free((*current).next);
    (*current).next = NULL; /// Remove The Link Between The Two
}

/// Remove First Function
void removeFirst(Node **root) {

    /// Does The Root Node Exits?
    if (*root == NULL)
        return;

    Node *toDelete = root;
    *root = (*root) -> next;
    toDelete -> next = NULL;
}

/// Get Length Function
int getLength(Node *root) {

    int length = 0;

    Node *current = root;
    while (current != NULL) {
        length++;
        current = current -> next;
    }

    return length;
}

void removeByValue(Node *root, Node **rootptr, int value) {

    /// If Target Node Is The Root Node
    if (root -> value == value) {
        removeFirst(rootptr);
        return;
    }

    /// If Target Node Is In The Middle
    Node *current = root;
    while (current -> next -> next != NULL) {

        if (current -> next -> value == value) {
            current -> next = current -> next -> next;
            return;
        }
        current = current -> next;
    }

    /// If Target Node Is The Last One
    if (current -> next -> value == value)
        current -> next = NULL;
}


