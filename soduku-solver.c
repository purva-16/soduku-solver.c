#include <stdio.h>
#include <stdlib.h>

// Define Node structure for linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define LinkedList structure
typedef struct LinkedList {
    Node* head;
} LinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new linked list
LinkedList* createLinkedList() {
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    return newList;
}

// Function to insert a value into a linked list
void insert(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

// Function to remove a value from a linked list
void removeNode(LinkedList* list, int data) {
    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Function to print the Sudoku grid
void printGrid(int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a number is valid in a specific position
int isValid(int grid[9][9], int row, int col, int num) {
    // Check row
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num) {
            return 0;
        }
    }

    // Check column
    for (int i = 0; i < 9; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle
int solveSudoku(int grid[9][9], LinkedList* emptyCells) {
    int row, col;

    // Find the next empty cell
    Node* current = emptyCells->head;
    if (current == NULL) {
        return 1; // If no empty cells, puzzle is solved
    }
    row = current->data / 9;
    col = current->data % 9;

    // Try filling in numbers 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            // Remove the cell from the empty cells list
            removeNode(emptyCells, row * 9 + col);

            if (solveSudoku(grid, emptyCells)) {
                return 1; // If a solution is found, return 1
            }

            // If no solution is found, backtrack
            grid[row][col] = 0;

            // Add the cell back to the empty cells list
            insert(emptyCells, row * 9 + col);
        }
    }

    return 0; // If no valid number is found, return 0
}

int main() {
    int grid[9][9];
    LinkedList* emptyCells = createLinkedList();

    printf("Enter the Sudoku puzzle (9x9 grid):\n");
    printf("Enter each row with 9 values separated by spaces. Use '0' for empty cells.\n");

    for (int i = 0; i < 9; i++) {
        printf("Enter values for row %d: ", i + 1);

        for (int j = 0; j < 9; j++) {
            scanf("%d", &grid[i][j]);

            // If the entered value is 0, add it to the empty cells linked list
            if (grid[i][j] == 0) {
                insert(emptyCells, i * 9 + j);
            }
        }
    }

    if (solveSudoku(grid, emptyCells)) {
        printf("Sudoku solved:\n");
        printGrid(grid);
    } else {
        printf("No solution exists\n");
    }

    free(emptyCells);
    return 0;
}
