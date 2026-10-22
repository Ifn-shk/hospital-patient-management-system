
# Hospital Patient Management System Using Stack and Queue

## Problem Statement

Develop a Hospital Patient Management System in C using the Stack and Queue data structures to manage waiting patients and maintain a history of served patients.

## Objectives

- Manage patients waiting for medical service.
- Serve patients in the order they arrive.
- Maintain a history of patients who have been served.
- Demonstrate the practical use of Stack and Queue in C.

## Data Structures Used

### 1. Queue (FIFO)

Queue stands for First In, First Out.

- New patients are added at the rear.
- The next patient is served from the front.
- The patient who arrives first is served first.

### 2. Stack (LIFO)

Stack stands for Last In, First Out.

- After a patient is served, their details are pushed onto the stack.
- The most recently served patient is displayed first in the history.

## Features

1. Add a new patient.
2. Display the waiting patient list.
3. Serve the next patient.
4. Display served patient history.
5. Display waiting and served patient counts.
6. Validate patient IDs and basic input.
7. Handle empty and full data structures.

## Technologies Used

- Programming Language: C
- Concepts: Structures, Functions, Arrays, Stack, Queue
- Compiler: GCC or any compatible C compiler

## How to Compile and Run

### Windows (using GCC)

Compile:

```bash
gcc hospital_management.c -o hospital_management
```

Run:

```bash
hospital_management.exe
```

### Linux or macOS

Compile:

```bash
gcc hospital_management.c -o hospital_management
```

Run:

```bash
./hospital_management
```

## Sample Workflow

1. Select option 1 to add a patient.
2. Enter the patient's ID, name, age, and condition.
3. Add another patient if required.
4. Select option 2 to view the waiting list in FIFO order.
5. Select option 3 to serve the next patient.
6. Select option 4 to view served patients in LIFO order.
7. Select option 5 to view patient counts.

## Limitations

- The system supports a maximum of 100 waiting patients and 100 served-patient history entries.
- Patient records are stored in memory and are not saved after the program exits.
- This is an educational project and is not intended for use in a real hospital.

## Conclusion

The Hospital Patient Management System demonstrates how a Queue can manage patients waiting for service and how a Stack can maintain the history of served patients. This project provides a practical example of applying fundamental data structures to a real-world problem.
