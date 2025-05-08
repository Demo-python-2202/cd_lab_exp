#include <stdio.h>
#include <string.h>
#define MAX 10

// Symbol structure
typedef struct {
    char name[20];
    char type[10];
    int size;
} Symbol;

Symbol table[MAX];
int count = 0;

// Insert a symbol into the table
void insert(char* name, char* type, int size) {
    if (count >= MAX) {
        printf("Symbol Table Full!\n");
        return;
    }
    strcpy(table[count].name, name);
    strcpy(table[count].type, type);
    table[count].size = size;
    count++;
}

// Search for a symbol in the table
void search(char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            printf("Found: %s (%s, Size: %d)\n", table[i].name, table[i].type, table[i].size);
            return;
        }
    }
    printf("Symbol not found.\n");
}

// Display the symbol table
void display() {
    printf("\nSymbol Table:\n-------------------------\n");
    printf("Name\tType\tSize\n");
    printf("-------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%s\t%s\t%d\n", table[i].name, table[i].type, table[i].size);
    printf("-------------------------\n");
}

int main() {
    insert("x", "int", 4);
    insert("y", "float", 4);
    insert("arr", "int[10]", 40);

    display();

    printf("\nSearch symbol: ");
    char key[20];
    scanf("%19s", key);  // Prevents buffer overflow

    search(key);
    return 0;
}
