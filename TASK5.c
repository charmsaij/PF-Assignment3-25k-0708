#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define INITIAL_CAPACITY 4
#define MAX_INPUT 1024
int i;
void insertLine(char ***lines, int *count, int *capacity, int index, const char *text);
void deleteLine(char ***lines, int *count, int index);
void printAllLines(char **lines, int count);
void freeAll(char ***lines, int *count, int *capacity);
void shrinkToFit(char ***lines, int *capacity, int count);
void saveToFile(char **lines, int count, const char *filename);
void loadFromFile(char ***lines, int *count, int *capacity, const char *filename);

int main() {
    char **lines = NULL;
    int count = 0;
    int capacity = INITIAL_CAPACITY;

    lines = (char**)malloc(capacity * sizeof(char*));
    if (!lines) {
        perror("malloc failed");
        exit(1);
    }

    int choice;
    char buffer[MAX_INPUT];

    while (1) {
        printf("\n--- Minimal Text Editor ---\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink To Fit\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("Enter position to insert: ");
            int pos;  
            scanf("%d", &pos);
            getchar();
            printf("Enter text: ");
            fgets(buffer, MAX_INPUT, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            insertLine(&lines, &count, &capacity, pos, buffer);
        }

        else if (choice == 2) {
            printf("Enter line number to delete: ");
            int pos;
            scanf("%d", &pos);
            getchar();
            deleteLine(&lines, &count, pos);
        }

        else if (choice == 3) {
            printAllLines(lines, count);
        }

        else if (choice == 4) {
            shrinkToFit(&lines, &capacity, count);
        }

        else if (choice == 5) {
            char filename[100];
            printf("Enter filename: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = 0;
            saveToFile(lines, count, filename);
        }

        else if (choice == 6) {
            char filename[100];
            printf("Enter filename: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = 0;
            loadFromFile(&lines, &count, &capacity, filename);
        }

        else if (choice == 7) {
            freeAll(&lines, &count, &capacity);
            printf("Exiting...\n");
            break;
        }
    }

    return 0;
}

void insertLine(char ***lines, int *count, int *capacity, int index, const char *text) {
    if (index < 0 || index > *count) {
        printf("Invalid index!\n");
        return;
    }
    if (*count == *capacity) {
        *capacity *= 2;
        char **temp = realloc(*lines, (*capacity) * sizeof(char*));
        if (!temp) {
            perror("realloc failed");
            exit(1);
        }
        *lines = temp;
    }
    memmove(&(*lines)[index + 1], &(*lines)[index], (*count - index) * sizeof(char*));
    (*lines)[index] = malloc(strlen(text) + 1);
    if (!(*lines)[index]) {
        perror("malloc failed");
        exit(1);
    }
    strcpy((*lines)[index], text);
    (*count)++;
}

void deleteLine(char ***lines, int *count, int index) {
    if (index < 0 || index >= *count) {
        printf("Invalid index!\n");
        return;
    }
    free((*lines)[index]);
    memmove(&(*lines)[index], &(*lines)[index + 1], (*count - index - 1) * sizeof(char*));
    (*count)--;
}

void printAllLines(char **lines, int count) {
    if (count == 0) {
        printf("Buffer is empty.\n");
        return;
    }
    for (i = 0; i < count; i++)
        printf("%d: %s\n", i, lines[i]);
}

void shrinkToFit(char ***lines, int *capacity, int count) {
    char **temp = realloc(*lines, count * sizeof(char*));
    if (!temp) {
        perror("realloc failed");
        return;
    }
    *lines = temp;
    *capacity = count;
    printf("Memory shrunk to %d lines.\n", count);
}

void saveToFile(char **lines, int count, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File could not be opened");
        return;
    }
    for (i = 0; i < count; i++)
        fprintf(fp, "%s\n", lines[i]);
    fclose(fp);
    printf("Saved successfully.\n");
}

void loadFromFile(char ***lines, int *count, int *capacity, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File not found");
        return;
    }
    freeAll(lines, count, capacity);
    *capacity = INITIAL_CAPACITY;
    *count = 0;
    *lines = malloc((*capacity) * sizeof(char*));
    if (!(*lines)) {
        perror("malloc failed");
        exit(1);
    }
    char buffer[MAX_INPUT];
    while (fgets(buffer, MAX_INPUT, fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        insertLine(lines, count, capacity, *count, buffer);
    }
    fclose(fp);
    printf("File loaded successfully.\n");
}

void freeAll(char ***lines, int *count, int *capacity) {
    for (i = 0; i < *count; i++)
        free((*lines)[i]);
    free(*lines);
    *lines = NULL;
    *count = 0;
    *capacity = 0;
}

