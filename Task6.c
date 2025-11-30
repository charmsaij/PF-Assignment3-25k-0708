#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "members.dat"
int i,j;
typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char regDate[20];
    char dob[20];
    char interest[10];
} Student;

Student *records = NULL;
int count = 0;
int capacity = 0;

void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    count = size / sizeof(Student);
    capacity = count;
    records = malloc(capacity * sizeof(Student));
    fread(records, sizeof(Student), count, fp);
    fclose(fp);
}

void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error saving.\n");
        return;
    }
    fwrite(records, sizeof(Student), count, fp);
    fclose(fp);
}

int existsID(int id) {
    for (i = 0; i < count; i++)
        if (records[i].studentID == id)
            return 1;
    return 0;
}

void addStudentToMemory(Student s) {
    if (existsID(s.studentID)) {
        printf("Duplicate ID not allowed.\n");
        return;
    }
    if (count == capacity) {
        capacity = capacity == 0 ? 2 : capacity * 2;
        records = realloc(records, capacity * sizeof(Student));
    }
    records[count++] = s;
    saveDatabase(FILE_NAME);
    printf("Student added.\n");
}

void updateStudent(int id) {
    for (i = 0; i < count; i++) {
        if (records[i].studentID == id) {
            printf("New Batch: ");
            scanf("%s", records[i].batch);
            printf("New Membership Type: ");
            scanf("%s", records[i].membershipType);
            saveDatabase(FILE_NAME);
            printf("Updated.\n");
            return;
        }
    }
    printf("ID not found.\n");
}

void deleteStudent(int id) {
    int found = 0;
    for (i = 0; i < count; i++) {
        if (records[i].studentID == id) {
            found = 1;
            for (j = i; j < count - 1; j++)
                records[j] = records[j + 1];
            count--;
            saveDatabase(FILE_NAME);
            printf("Deleted.\n");
            return;
        }
    }
    if (!found)
        printf("ID not found.\n");
}

void viewAll() {
    if (count == 0) {
        printf("No records.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nBatch: %s\nMembership: %s\nReg Date: %s\nDOB: %s\nInterest: %s\n",
               records[i].studentID,
               records[i].fullName,
               records[i].batch,
               records[i].membershipType,
               records[i].regDate,
               records[i].dob,
               records[i].interest);
    }
}

void batchReport() {
    char batch[20], type[10];
    printf("Enter Batch (CS/SE/AI/Cyber): ");
    scanf("%s", batch);
    printf("Enter Type (IEEE/ACM/Both): ");
    scanf("%s", type);

    int found = 0;
    for (i = 0; i < count; i++) {
        if (strcmp(records[i].batch, batch) == 0 &&
            strcmp(records[i].interest, type) == 0) {
            found = 1;
            printf("\nID: %d | %s\n", records[i].studentID, records[i].fullName);
        }
    }
    if (!found) printf("No matching records.\n");
}

int main() {
    loadDatabase(FILE_NAME);

    while (1) {
        int choice;
        printf("\n--- Membership Manager ---\n");
        printf("1. Register Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All\n");
        printf("5. Batch Report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Student s;
            printf("Student ID: ");
            scanf("%d", &s.studentID);
            getchar();
            printf("Full Name: ");
            fgets(s.fullName, 100, stdin);
            s.fullName[strcspn(s.fullName, "\n")] = 0;
            printf("Batch: ");
            scanf("%s", s.batch);
            printf("Membership (IEEE/ACM): ");
            scanf("%s", s.membershipType);
            printf("Registration Date (YYYY-MM-DD): ");
            scanf("%s", s.regDate);
            printf("DOB (YYYY-MM-DD): ");
            scanf("%s", s.dob);
            printf("Interest (IEEE/ACM/Both): ");
            scanf("%s", s.interest);
            addStudentToMemory(s);
        }

        else if (choice == 2) {
            int id;
            printf("Enter ID to update: ");
            scanf("%d", &id);
            updateStudent(id);
        }

        else if (choice == 3) {
            int id;
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            deleteStudent(id);
        }

        else if (choice == 4) {
            viewAll();
        }

        else if (choice == 5) {
            batchReport();
        }

        else if (choice == 6) {
            saveDatabase(FILE_NAME);
            free(records);
            printf("Exiting...\n");
            break;
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

