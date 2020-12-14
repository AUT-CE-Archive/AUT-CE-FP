#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// Developed By: Keivan Ipchi Hagh - All Rights Reserved ///

/// Create & Rename Structs
typedef struct Student {
    char *id;
    char *phoneNumber;
} Student;

typedef struct List {
    int length;
    struct Node *root;
} List;

typedef struct Node {
    Student *student;
    struct Node *next;
} Node;

int printMenu() {
    printf("1) Add\n2) Remove\n3) List\n4) Quit\n");
    int result;
    scanf("%d", &result);
    return result;
}

void traverse(List *list) {

    Node *current = list -> root;
    int counter = 0;
    while (current != NULL) {
        printf("%d)\nNo: %s\nPhone: %s\n", counter + 1, current -> student -> id, current -> student -> phoneNumber);
        current = current -> next;
        counter++;
    }
}

List* createList() {
    List *list = (List*)malloc(sizeof(List));
    list -> length = 0;
    list -> root = NULL;
    return list;
}

Node* createNode() {
    Node *node = (Node*)malloc(sizeof(Node));
    node -> student = NULL;
    node -> next = NULL;
    return node;
}

Student* createStudent(char id[8], char phoneNumber[12]) {
    Student *student = (Student*)malloc(sizeof(Student));
    student -> id = id;
    student -> phoneNumber = phoneNumber;
    return student;
}

void addLast(List *list, Student *student) {

    Node *node = createNode();
    node -> next = NULL;
    node -> student = student;

	/// New list? Np Add To Root
    if (list -> root == NULL) {
        list -> root = node;
        return;
    }

	/// Otherwise
    Node *current = list -> root;
    while (current -> next != NULL)
        current = current -> next;

    current -> next = node;
}

void removeByID(List *list, char *id) {

	Node *current = list -> root;

	/// What If We Want To Remove The Root? (First Node!!!)
	if (strcmp(current -> student -> id, id) == 0) {
		list -> root = current -> next;
		return;
	}

	/// What If It's From The Middle??!
	current = list -> root;
	while (current -> next -> next != NULL) {

		if (strcmp(current -> next -> student -> id , id) == 0) {
			current -> next = current -> next -> next;
			return;
		}
		current = current -> next;
	}

	/// What If It's The Last Node?!
	current = list -> root;
	while (current -> next -> next != NULL)	/// Iterate To The Last Existing Node
		current = current -> next;
	current -> next = NULL;
}

bool seachByID(List *list, char *id) {

	Node *current = list -> root;

	while (current!= NULL) {
		if (strcmp(current -> student -> id, id) == 0)
			return true;
		current = current -> next;
	}
	return false;
}

int main() {

    List *list = createList();

    while(true) {

    	int option = printMenu();
    	char *id = (char*)malloc(sizeof(char) * 8);
    	char *phoneNumber = (char*)malloc(sizeof(char) * 12);

        switch(option) {
            case 1:

				/// Add new Student
				printf("No: ");
    			scanf("%s", id);
    			printf("Phone: ");
    			scanf("%s", phoneNumber);
    			Student *student = createStudent(id, phoneNumber);
    			addLast(list, student);
			break;

            case 2:

				printf("No: ");
				scanf("%s", id);
				if (seachByID(list, id) == true) {
					removeByID(list, id);
					printf("%s has been removed\n", id);
				}
				else
					printf("%s does not exist\n", id);

			break;
            case 3: traverse(list); break;
            case 4: return 0; break;
        }
    }

    return 0;
}

