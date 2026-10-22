
#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NAME_LENGTH 50
#define DISEASE_LENGTH 100

typedef struct {
    int id;
    char name[NAME_LENGTH];
    int age;
    char disease[DISEASE_LENGTH];
} Patient;

/* Queue: patients waiting to be served (FIFO) */
typedef struct {
    Patient items[MAX_PATIENTS];
    int front;
    int rear;
    int count;
} PatientQueue;

/* Stack: patients who have already been served (LIFO) */
typedef struct {
    Patient items[MAX_PATIENTS];
    int top;
} PatientStack;

/* Read an integer safely */
int readInt(const char *prompt) {
    int value;
    int result;
    int ch;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Clear remaining input */
        }

        if (result == 1) {
            return value;
        }

        printf("Invalid input. Please enter a number.\n");
    }
}

/* Read a line of text */
void readText(const char *prompt, char *text, int size) {
    printf("%s", prompt);

    if (fgets(text, size, stdin) != NULL) {
        size_t length = strlen(text);

        if (length > 0 && text[length - 1] == '\n') {
            text[length - 1] = '\0';
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Clear remaining input */
            }
        }
    }
}

/* Initialise the queue */
void initializeQueue(PatientQueue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

/* Initialise the stack */
void initializeStack(PatientStack *stack) {
    stack->top = -1;
}

/* Check whether a patient ID is already in use */
int idExists(const PatientQueue *queue,
             const PatientStack *stack, int id) {
    int i;

    for (i = 0; i < queue->count; i++) {
        int index = (queue->front + i) % MAX_PATIENTS;

        if (queue->items[index].id == id) {
            return 1;
        }
    }

    for (i = 0; i <= stack->top; i++) {
        if (stack->items[i].id == id) {
            return 1;
        }
    }

    return 0;
}

/* Add a patient to the rear of the queue */
int enqueue(PatientQueue *queue, Patient patient) {
    if (queue->count == MAX_PATIENTS) {
        return 0;
    }

    queue->rear = (queue->rear + 1) % MAX_PATIENTS;
    queue->items[queue->rear] = patient;
    queue->count++;

    return 1;
}

/* Remove the next patient from the front of the queue */
int dequeue(PatientQueue *queue, Patient *patient) {
    if (queue->count == 0) {
        return 0;
    }

    *patient = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_PATIENTS;
    queue->count--;

    if (queue->count == 0) {
        queue->front = 0;
        queue->rear = -1;
    }

    return 1;
}

/* Push a served patient onto the stack */
int push(PatientStack *stack, Patient patient) {
    if (stack->top == MAX_PATIENTS - 1) {
        return 0;
    }

    stack->items[++stack->top] = patient;
    return 1;
}

/* Display patient information */
void displayPatient(Patient patient) {
    printf("ID: %d | Name: %s | Age: %d | Condition: %s\n",
           patient.id, patient.name,
           patient.age, patient.disease);
}

/* Add a new patient */
void addPatient(PatientQueue *queue, PatientStack *stack) {
    Patient patient;

    if (queue->count == MAX_PATIENTS) {
        printf("\nWaiting queue is full.\n");
        return;
    }

    patient.id = readInt("Enter patient ID: ");

    if (patient.id <= 0) {
        printf("Patient ID must be positive.\n");
        return;
    }

    if (idExists(queue, stack, patient.id)) {
        printf("This patient ID already exists.\n");
        return;
    }

    readText("Enter patient name: ",
             patient.name, NAME_LENGTH);

    if (patient.name[0] == '\0') {
        printf("Patient name cannot be empty.\n");
        return;
    }

    patient.age = readInt("Enter patient age: ");

    if (patient.age < 0 || patient.age > 130) {
        printf("Please enter a valid age (0-130).\n");
        return;
    }

    readText("Enter condition/disease: ",
             patient.disease, DISEASE_LENGTH);

    if (patient.disease[0] == '\0') {
        printf("Condition cannot be empty.\n");
        return;
    }

    if (enqueue(queue, patient)) {
        printf("\nPatient added to the waiting queue successfully.\n");
    } else {
        printf("Unable to add patient. Queue is full.\n");
    }
}

/* Display patients in FIFO order */
void displayWaitingPatients(const PatientQueue *queue) {
    int i;

    if (queue->count == 0) {
        printf("\nNo patients are waiting.\n");
        return;
    }

    printf("\n--- Waiting Patients (FIFO) ---\n");

    for (i = 0; i < queue->count; i++) {
        int index = (queue->front + i) % MAX_PATIENTS;
        displayPatient(queue->items[index]);
    }
}

/* Serve the next patient and save them in the stack */
void serveNextPatient(PatientQueue *queue, PatientStack *stack) {
    Patient patient;

    if (queue->count == 0) {
        printf("\nNo patients are waiting to be served.\n");
        return;
    }

    if (stack->top == MAX_PATIENTS - 1) {
        printf("\nServed-patient history is full.\n");
        return;
    }

    dequeue(queue, &patient);
    push(stack, patient);

    printf("\nPatient served successfully:\n");
    displayPatient(patient);
}

/* Display served patients in LIFO order */
void displayServedPatients(const PatientStack *stack) {
    int i;

    if (stack->top == -1) {
        printf("\nNo patients have been served yet.\n");
        return;
    }

    printf("\n--- Served Patient History (LIFO) ---\n");

    for (i = stack->top; i >= 0; i--) {
        displayPatient(stack->items[i]);
    }
}

int main(void) {
    PatientQueue waitingQueue;
    PatientStack servedStack;
    int choice;

    initializeQueue(&waitingQueue);
    initializeStack(&servedStack);

    do {
        printf("\n===== HOSPITAL PATIENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add a patient\n");
        printf("2. Display waiting patients\n");
        printf("3. Serve next patient\n");
        printf("4. Display served patient history\n");
        printf("5. Display patient counts\n");
        printf("0. Exit\n");

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addPatient(&waitingQueue, &servedStack);
                break;

            case 2:
                displayWaitingPatients(&waitingQueue);
                break;

            case 3:
                serveNextPatient(&waitingQueue, &servedStack);
                break;

            case 4:
                displayServedPatients(&servedStack);
                break;

            case 5:
                printf("\nPatients waiting: %d\n",
                       waitingQueue.count);
                printf("Patients served: %d\n",
                       servedStack.top + 1);
                break;

            case 0:
                printf("\nExiting Hospital Patient Management System.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

