#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.dat"

typedef struct {
    int studentID;
    char fullName[100];
    char batch[50]; 
    char membershipType[10]; 
    char registrationDate[11]; 
    char dob[11]; 
    char interest[10]; 
} Student;

Student *students = NULL;
int studentCount = 0;

// Function Prototypes
void loadDatabase(const char *filename);
void saveDatabase(const char *filename);
void addStudent(const char *filename);
void updateStudent();
void deleteStudent();
void displayAllStudents();
void generateBatchReport();
int findStudentIndexByID(int id);
int checkDuplicateID(int id);

// Utility function to flush input buffer
void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Load all students from file into memory
void loadDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    studentCount = fileSize / sizeof(Student);
    students = (Student *)malloc(studentCount * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed!\n");
        fclose(file);
        exit(1);
    }

    if (fread(students, sizeof(Student), studentCount, file) != studentCount) {
        printf("Error reading database!\n");
    }
    fclose(file);
}

// Save all students from memory to file
void saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    if (fwrite(students, sizeof(Student), studentCount, file) != studentCount) {
        printf("Error writing to file!\n");
    } else {
        printf("Database saved successfully.\n");
    }
    fclose(file);
}

// Check if student ID is duplicate
int checkDuplicateID(int id) {
	int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].studentID == id)
            return 1; 
    }
    return 0; 
}

// Add a new student
void addStudent(const char *filename) {
    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);
    flushInput();

    if (checkDuplicateID(s.studentID)) {
        printf("Student ID already exists! Cannot add.\n");
        return;
    }

    printf("Enter Full Name: ");
    fgets(s.fullName, sizeof(s.fullName), stdin);
    s.fullName[strcspn(s.fullName, "\n")] = 0; // remove newline

    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    fgets(s.batch, sizeof(s.batch), stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;

    printf("Enter Membership Type (IEEE/ACM): ");
    fgets(s.membershipType, sizeof(s.membershipType), stdin);
    s.membershipType[strcspn(s.membershipType, "\n")] = 0;

    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.registrationDate, sizeof(s.registrationDate), stdin);
    s.registrationDate[strcspn(s.registrationDate, "\n")] = 0;

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dob, sizeof(s.dob), stdin);
    s.dob[strcspn(s.dob, "\n")] = 0;

    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(s.interest, sizeof(s.interest), stdin);
    s.interest[strcspn(s.interest, "\n")] = 0;

    // Add to dynamic array
    students = (Student *)realloc(students, (studentCount + 1) * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    students[studentCount++] = s;

    // Append to file
    FILE *file = fopen(filename, "ab");
    if (!file) {
        printf("Error opening file for appending!\n");
        return;
    }
    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    printf("Student added successfully!\n");
}

// Find index of student by ID
int findStudentIndexByID(int id) {
	int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].studentID == id)
            return i;
    }
    return -1;
}

// Update student information
void updateStudent() {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    flushInput();

    int index = findStudentIndexByID(id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Current Batch: %s\n", students[index].batch);
    printf("Enter new Batch (CS/SE/Cyber Security/AI): ");
    fgets(students[index].batch, sizeof(students[index].batch), stdin);
    students[index].batch[strcspn(students[index].batch, "\n")] = 0;

    printf("Current Membership Type: %s\n", students[index].membershipType);
    printf("Enter new Membership Type (IEEE/ACM): ");
    fgets(students[index].membershipType, sizeof(students[index].membershipType), stdin);
    students[index].membershipType[strcspn(students[index].membershipType, "\n")] = 0;

    saveDatabase(FILENAME);
    printf("Student information updated successfully.\n");
}

// Delete a student
void deleteStudent() {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    flushInput();

    int index = findStudentIndexByID(id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    // Shift elements left
    int i;
    for (i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    students = (Student *)realloc(students, studentCount * sizeof(Student));
    saveDatabase(FILENAME);
    printf("Student deleted successfully.\n");
}

// Display all students
void displayAllStudents() {
    if (studentCount == 0) {
        printf("No students registered yet.\n");
        return;
    }

    printf("All Registered Students:\n");
    printf("ID\tName\tBatch\tMembership\tReg Date\tDOB\tInterest\n");
    int i;
    for (i = 0; i < studentCount; i++) {
        Student s = students[i];
        printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
               s.studentID, s.fullName, s.batch, s.membershipType, s.registrationDate, s.dob, s.interest);
    }
}

// Generate batch-wise report
void generateBatchReport() {
    char batch[50];
    printf("Enter Batch to generate report (CS/SE/Cyber Security/AI): ");
    flushInput();
    fgets(batch, sizeof(batch), stdin);
    batch[strcspn(batch, "\n")] = 0;

    int found = 0;
    printf("Students in %s batch:\n", batch);
    printf("ID\tName\tMembership\tInterest\n");
    int i;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            Student s = students[i];
            printf("%d\t%s\t%s\t%s\n", s.studentID, s.fullName, s.membershipType, s.interest);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in this batch.\n");
    }
}

// Main menu
void menu() {
    int choice;
    do {
        printf("\n--- IEEE & ACM Membership System ---\n");
        printf("1. Register a new student\n");
        printf("2. Update student information\n");
        printf("3. Delete student registration\n");
        printf("4. View all registrations\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        flushInput();

        switch (choice) {
            case 1:
                addStudent(FILENAME);
                break;
            case 2:
                updateStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                displayAllStudents();
                break;
            case 5:
                generateBatchReport();
                break;
            case 6:
                saveDatabase(FILENAME);
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
}

int main() {
    loadDatabase(FILENAME);
    menu();
    free(students); // free dynamic memory
    return 0;
}
