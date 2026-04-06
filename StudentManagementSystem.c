#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float grade;
};

void addStudent() {
    FILE *f = fopen("students.txt", "ab");
    struct Student s;

    if (f == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter id: ");
    scanf("%d", &s.id);

    printf("Enter name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter grade: ");
    scanf("%f", &s.grade);

    fwrite(&s, sizeof(s), 1, f);
    fclose(f);

    printf("Added.\n");
}

void displayStudents() {
    FILE *f = fopen("students.txt", "rb");
    struct Student s;

    if (f == NULL) {
        printf("No data.\n");
        return;
    }

    printf("\nStudents:\n");

    while (fread(&s, sizeof(s), 1, f)) {
        printf("%d %s %.2f\n", s.id, s.name, s.grade);
    }

    fclose(f);
}

void searchStudent() {
    FILE *f = fopen("students.txt", "rb");
    struct Student s;
    int id, found = 0;

    if (f == NULL) {
        printf("No data.\n");
        return;
    }

    printf("Enter id: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id == id) {
            printf("Found: %d %s %.2f\n", s.id, s.name, s.grade);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Not found.\n");

    fclose(f);
}

void deleteStudent() {
    FILE *f = fopen("students.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    struct Student s;
    int id, found = 0;

    if (f == NULL) {
        printf("No data.\n");
        return;
    }

    printf("Enter id to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Deleted.\n");
    else
        printf("Not found.\n");
}

void updateStudent() {
    FILE *f = fopen("students.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    struct Student s;
    int id, found = 0;

    if (f == NULL) {
        printf("No data.\n");
        return;
    }

    printf("Enter id to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter new grade: ");
            scanf("%f", &s.grade);

            found = 1;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(f);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Updated.\n");
    else
        printf("Not found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1 Add\n2 Display\n3 Search\n4 Delete\n5 Update\n6 Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            addStudent();
        else if (choice == 2)
            displayStudents();
        else if (choice == 3)
            searchStudent();
        else if (choice == 4)
            deleteStudent();
        else if (choice == 5)
            updateStudent();
        else if (choice == 6)
            break;
        else
            printf("Invalid choice\n");
    }

    return 0;
}