
#include <stdio.h>

#define MAX 100

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

struct Patient patients[MAX];
int count = 0;

void addPatient() {
    if (count >= MAX) {
        printf("Patient records are full!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &patients[count].id);

    printf("Enter Patient Name: ");
    scanf(" %49[^\n]", patients[count].name);

    printf("Enter Patient Age: ");
    scanf("%d", &patients[count].age);

    printf("Enter Disease: ");
    scanf(" %49[^\n]", patients[count].disease);

    count++;
    printf("\nPatient added successfully!\n");
}

void displayPatients() {
    if (count == 0) {
        printf("\nNo patient records found.\n");
        return;
    }

    printf("\n--- Patient Records ---\n");

    for (int i = 0; i < count; i++) {
        printf("\nPatient ID: %d\n", patients[i].id);
        printf("Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Disease: %s\n", patients[i].disease);
    }
}

int main() {
    int choice;

    do {
        printf("\n===== Hospital Patient Management System =====\n");
        printf("1. Add Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                printf("Thank you for using the system!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}
