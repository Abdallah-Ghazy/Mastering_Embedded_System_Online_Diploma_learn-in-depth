#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Color codes for console text
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BRIGHT_CYAN    "\033[96m"

// Student data structure
struct SData {
    int ID;
    char name[40];
    float height;
};

struct SStudent {
    struct SData student;
    struct SStudent* PNextStudent;
};

struct SStudent* gpFirstStudent = NULL;

// Function prototypes
void AddStudent(void);
void ViewStudent(void);
void DeleteStudent(void);
void DeleteAll(void);
void GetNth(void);
void FindLength(struct SStudent* pCurrentStudent, int* count);
void NodeFromEnd(void);

// Function to add a student to the list
void AddStudent(void) {
    printf("\n" BRIGHT_CYAN "=====================================" RESET);
    printf("\n" BRIGHT_CYAN "   Entering AddStudent function..." RESET);
    printf("\n" BRIGHT_CYAN "=====================================" RESET "\n");

    struct SStudent* pNewStudent;
    struct SStudent* pLastStudent;
    char temp[40];

    pNewStudent = (struct SStudent*) malloc(sizeof(struct SStudent));
    if (pNewStudent == NULL) {
        printf("\n" RED "Error: Memory allocation failed." RESET "\n\n");
        return;
    }

    if (gpFirstStudent == NULL) {
        gpFirstStudent = pNewStudent;
        pNewStudent->PNextStudent = NULL;
    } else {
        pLastStudent = gpFirstStudent;
        while (pLastStudent->PNextStudent)
            pLastStudent = pLastStudent->PNextStudent;

        pLastStudent->PNextStudent = pNewStudent;
        pNewStudent->PNextStudent = NULL;
    }

    printf("\nEnter the ID: ");
    fgets(temp, sizeof(temp), stdin);
    pNewStudent->student.ID = atoi(temp);

    printf("\nEnter Student full name: ");
    fgets(pNewStudent->student.name, sizeof(pNewStudent->student.name), stdin);
    pNewStudent->student.name[strcspn(pNewStudent->student.name, "\n")] = '\0'; // Remove newline character

    printf("\nEnter the height: ");
    fgets(temp, sizeof(temp), stdin);
    pNewStudent->student.height = atof(temp);

    printf("\n" GREEN "Student added successfully!" RESET "\n\n");
}

// Function to view all students
void ViewStudent(void) {
    printf("\n" BLUE "=====================================" RESET);
    printf("\n" BLUE "  Entering ViewStudent function..." RESET);
    printf("\n" BLUE "=====================================" RESET "\n");

    struct SStudent* pCurrentStudent = gpFirstStudent;
    int count = 0;
    if (gpFirstStudent == NULL) {
        printf("\n" YELLOW "The List is empty." RESET "\n\n");
    } else {
        printf("\n" BLUE "+----+-----------------------+--------+" RESET "\n");
        printf("| ID | Name                  | Height |" RESET "\n");
        printf("+----+-----------------------+--------+" RESET "\n");
        while (pCurrentStudent) {
            printf("| %-2d | %-21s | %-6.2f |\n", pCurrentStudent->student.ID, pCurrentStudent->student.name, pCurrentStudent->student.height);
            pCurrentStudent = pCurrentStudent->PNextStudent;
            count++;
        }
        printf("+----+-----------------------+--------+" RESET "\n\n");
    }
}

// Function to delete a student by ID
void DeleteStudent(void) {
    printf("\n" GREEN "=====================================" RESET);
    printf("\n" GREEN " Entering DeleteStudent function..." RESET);
    printf("\n" GREEN "=====================================" RESET "\n");

    char temp[40];
    unsigned int SelectID = 0;

    printf("\nEnter The Student ID to be Deleted: ");
    fgets(temp, sizeof(temp), stdin);
    SelectID = atoi(temp);

    if (gpFirstStudent) {
        struct SStudent* pSelectedStudent = gpFirstStudent;
        struct SStudent* pPreviousStudent = NULL;

        while (pSelectedStudent) {
            if (pSelectedStudent->student.ID == SelectID) {
                if (pPreviousStudent) {
                    pPreviousStudent->PNextStudent = pSelectedStudent->PNextStudent;
                } else {
                    gpFirstStudent = pSelectedStudent->PNextStudent;
                }
                free(pSelectedStudent);
                printf("\n" GREEN "Student deleted successfully!" RESET "\n\n");
                return;
            }
            pPreviousStudent = pSelectedStudent;
            pSelectedStudent = pSelectedStudent->PNextStudent;
        }
    }

    printf("\n" RED "Error: Can't find student ID." RESET "\n\n");
}

// Function to delete all students in the list
void DeleteAll(void) {
    printf("\n" GREEN "=====================================" RESET);
    printf("\n" GREEN "   Entering DeleteAll function..." RESET);
    printf("\n" GREEN "=====================================" RESET "\n");

    struct SStudent* pCurrentStudent = gpFirstStudent;
    if (gpFirstStudent == NULL) {
        printf("\n" YELLOW "The List is empty." RESET "\n\n");
    } else {
        while (pCurrentStudent) {
            struct SStudent* pTempStudent = pCurrentStudent;
            pCurrentStudent = pCurrentStudent->PNextStudent;
            free(pTempStudent);
        }
        gpFirstStudent = NULL;
        printf("\n" GREEN "All students have been deleted." RESET "\n\n");
    }
}

// Function to get the Nth student
void GetNth(void) {
    printf("\n" GREEN "=====================================" RESET);
    printf("\n" GREEN "     Entering GetNth function..." RESET);
    printf("\n" GREEN "=====================================" RESET "\n");

    printf("\nEnter the index: ");
    int index;
    fflush(stdout);  // Flush stdout buffer
    scanf("%d", &index);

    struct SStudent* pCurrentStudent = gpFirstStudent;
    int count = 0;

    if (index < 0) {
        printf("\n" RED "Error: Invalid index. Index must be non-negative." RESET "\n\n");
        return;
    }

    // Handle edge case for empty list
    if (gpFirstStudent == NULL) {
        printf("\n" YELLOW "The List is empty." RESET "\n\n");
        return;
    }

    // Traverse the list to find the Nth student
    while (pCurrentStudent != NULL) {
        if (count == index) {
            printf("\n" BLUE "+----+-----------------------+--------+" RESET "\n");
            printf("| ID | Name                  | Height |" RESET "\n");
            printf("+----+-----------------------+--------+" RESET "\n");
            printf("| %-2d | %-21s | %-6.2f |\n", pCurrentStudent->student.ID, pCurrentStudent->student.name, pCurrentStudent->student.height);
            printf("+----+-----------------------+--------+" RESET "\n\n");
            return;  // Exit the function once the student is found
        }
        pCurrentStudent = pCurrentStudent->PNextStudent;
        count++;
    }

    // Handle case where index is out of range
    printf("\n" RED "Error: Index out of range." RESET "\n\n");
}

// Function to find the length of the list
void FindLength(struct SStudent* pCurrentStudent, int* count) {
    if (pCurrentStudent == NULL) {
        printf("\n" GREEN "The length of the list is %d" RESET "\n\n", *count);
        return;
    }

    (*count)++;
    FindLength(pCurrentStudent->PNextStudent, count);
}

// Function to find the nth node from the end
void NodeFromEnd(void) {
    printf("\nEnter the n`th node from the end of a Linked List: ");
    int node, count = 0;
    fflush(stdout);
    scanf("%d", &node);

    if (node < 0) {
        printf("\n" RED "Error: Invalid node. Node must be non-negative." RESET "\n\n");
        return;
    }

    // Handle edge case for empty list
    if (gpFirstStudent == NULL) {
        printf("\n" YELLOW "The List is empty." RESET "\n\n");
        return;
    }

    struct SStudent* pmainPtr = gpFirstStudent;
    struct SStudent* prefPtr = gpFirstStudent;

    // Move prefPtr to the nth node
    for (int i = 0; i < node; i++) {
        if (prefPtr == NULL) {
            printf("\n" RED "Error: Node out of range." RESET "\n\n");
            return;
        }
        prefPtr = prefPtr->PNextStudent;
    }

    // Move both pointers until prefPtr reaches the end
    while (prefPtr != NULL) {
        pmainPtr = pmainPtr->PNextStudent;
        prefPtr = prefPtr->PNextStudent;
    }

    // pmainPtr now points to the nth node from the end
    if (pmainPtr) {
        printf("\n" BLUE "+----+-----------------------+--------+" RESET "\n");
        printf("| ID | Name                  | Height |" RESET "\n");
        printf("+----+-----------------------+--------+" RESET "\n");
        printf("| %-2d | %-21s | %-6.2f |\n", pmainPtr->student.ID, pmainPtr->student.name, pmainPtr->student.height);
        printf("+----+-----------------------+--------+" RESET "\n\n");
    } else {
        printf("\n" RED "Error: Node out of range." RESET "\n\n");
    }
}

// Main function to handle user choices
int main() {
    int choice;
    while (1) {
        printf("\n" GREEN "=====================================" RESET);
        printf("\n" GREEN "         STUDENT MANAGEMENT         " RESET);
        printf("\n" GREEN "=====================================" RESET);
        printf("\n1. Add Student");
        printf("\n2. View Students");
        printf("\n3. Delete Student by ID");
        printf("\n4. Delete All Students");
        printf("\n5. Get Nth Node");
        printf("\n6. Find Length");
        printf("\n7. Node From End");
        printf("\n9. Exit");
        printf("\n" GREEN "=====================================" RESET "\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        // Array of function pointers
        void (*menuFunctions[10])() = {
            NULL,        // Index 0
            AddStudent,  // Index 1
            ViewStudent, // Index 2
            DeleteStudent, // Index 3
            DeleteAll,   // Index 4
            GetNth,      // Index 5
            FindLength,  // Index 6
            NodeFromEnd, // Index 7
            NULL,        // Index 8 (for additional options if needed)
            NULL         // Index 9 (Exit)
        };

        // Check if the choice is valid and call the corresponding function
        if (choice >= 1 && choice <= 7) {
            if (choice == 6) {
                int length = 0;
                FindLength(gpFirstStudent, &length); // Pass the count by reference
            } else {
                menuFunctions[choice](); // Call the function
            }
        } else if (choice == 9) {
            DeleteAll(); // Clean up memory before exiting
            printf("\n" RED "Exiting..." RESET "\n");
            return 0;
        } else {
            printf("\n" RED "Invalid choice, please try again." RESET "\n\n");
        }
    }
}