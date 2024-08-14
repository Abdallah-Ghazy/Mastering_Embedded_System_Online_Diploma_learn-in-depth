/*
 * file.c
 *
 *  Created on: Aug 14, 2024
 *      Author: Abdallah Ghazy
 */


#include <stdio.h>
#include <stdlib.h>
#include "SMS.h"
#include <string.h>
Status WriteStudentToFile(const Registers *student, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return FILE_ERROR;
    }

    fprintf(file, "Roll Number: %d\n", student->Student.RollNumber);
    fprintf(file, "First Name: %s\n", student->Student.FirstName);
    fprintf(file, "Last Name: %s\n", student->Student.LastName);
    fprintf(file, "GPA: %.2f\n", student->Student.GPA);
    fprintf(file, "Email: %s\n", student->Student.Email);
    fprintf(file, "Course ID: %d\n", student->Course.CourseID);
    fprintf(file, "Course Name: %s\n", student->Course.CourseName);
    fprintf(file, "Registration Date: %s\n", student->RegistrationDate);
    fprintf(file, "----------------------------------------\n");

    fclose(file);
    return SUCCESS;
}

Status ReadStudentsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return FILE_ERROR;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return SUCCESS;
}

int GetLastStudentID(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int lastID = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int id;

        if (sscanf(line, "Roll Number: %d", &id) == 1) {
            lastID = id;
        }
    }

    fclose(file);
    return lastID;
}

Status DetailsfromFile(const char *filename) {
    FILE *file_src = fopen(filename, "r");
    if (file_src == NULL) {
        perror("Error opening source file");
        return FILE_ERROR;
    }

    FILE *file_des = fopen("students.txt", "a");
    if (file_des == NULL) {
        perror("Error opening destination file");
        fclose(file_src);
        return FILE_ERROR;
    }

    char line[256];

    while (fgets(line, sizeof(line), file_src)) {
        if (fputs(line, file_des) == EOF) {
            perror("Error writing to destination file");
            fclose(file_src);
            fclose(file_des);
            return FILE_ERROR;
        }
    }

    if (ferror(file_src)) {
        perror("Error reading from source file");
        fclose(file_src);
        fclose(file_des);
        return FILE_ERROR;
    }

    fclose(file_src);
    fclose(file_des);
    printf(BOLD YELLOW "\t\t\t ----- File details added successfully! -----\n" RESET);
    return SUCCESS;
}


void SearchByRollNumber(int rollNumber) {
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int id;
    int found = 0;
    int isPrinting = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Roll Number: %d", &id) == 1) {
            if (found && id != rollNumber) {
                break;
            }
            if (id == rollNumber) {
                found = 1;
                isPrinting = 1;
                printf("Details for Roll Number: %d\n", rollNumber);
            } else {
                isPrinting = 0;
            }
        }

        if (isPrinting) {
            printf("%s", line);
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", rollNumber);
    }

    fclose(file);
}

void SearchByFirstName(const char *firstName) {
    char line[MAX_LINE_LENGTH];

    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char previousLine[MAX_LINE_LENGTH] = "";
    int found = 0;
    int isPrinting = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "First Name: %s", name) == 1) {
            if (found && strcmp(name, firstName) != 0) {
                break;
            }
            if (strcmp(name, firstName) == 0) {
                found = 1;
                isPrinting = 1;
                printf("Details for First Name: %s\n", firstName);
            } else {
                isPrinting = 0;
            }
        }

        if (isPrinting) {
            printf("%s", previousLine);
        }

        strncpy(previousLine, line, sizeof(previousLine));
    }

    if (!found) {
        printf("Student with First Name %s not found.\n", firstName);
    }

    fclose(file);
}

void StudentsRegisteredinCourse(int CourseID) {
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int id;
    int isPrinting = 0;

    while (fgets(line, sizeof(line), file)) {

        if (sscanf(line, "Course ID: %d", &id) == 1) {
            if (id == CourseID) {
                isPrinting = 1;
            } else {
                isPrinting = 0;
            }
        }


        if (isPrinting) {
            printf("%s", line);
        }
    }

    fclose(file);
}

void CountOfStudents() {
    char line[MAX_LINE_LENGTH];
    int count = 0;

    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Roll Number:") != NULL) {
            count++;
        }
    }

    fclose(file);
    printf("Total number of students: %d\n", count);
}


void FDeleteStudent(int rollNumber) {
    char line[MAX_LINE_LENGTH];
    int found = 0;
    FILE *file = fopen("students.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Roll Number:") != NULL) {
            int currentRollNumber;
            sscanf(line, "Roll Number: %d", &currentRollNumber);
            if (currentRollNumber == rollNumber) {
                found = 1;

                while (fgets(line, sizeof(line), file)) {
                    if (strcmp(line, "----------------------------------------\n") == 0) {
                        break;
                    }
                }
            } else {
                fputs(line, tempFile);
            }
        } else if (!found) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student with Roll Number %d deleted successfully.\n", rollNumber);
    } else {
        printf("Student with Roll Number %d not found.\n", rollNumber);
    }
}

void F_UpdateStudent(int rollNumber, const char* newFirstName, const char* newLastName, float newGPA, const char* newEmail) {
    char line[MAX_LINE_LENGTH];
    int found = 0;
    FILE *file = fopen("students.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Roll Number:") != NULL) {
            int currentRollNumber;
            sscanf(line, "Roll Number: %d", &currentRollNumber);
            if (currentRollNumber == rollNumber) {
                found = 1;
                fprintf(tempFile, "Roll Number: %d\n", rollNumber);
                fprintf(tempFile, "First Name: %s\n", newFirstName);
                fprintf(tempFile, "Last Name: %s\n", newLastName);
                fprintf(tempFile, "GPA: %.2f\n", newGPA);
                fprintf(tempFile, "Email: %s\n", newEmail);

                while (fgets(line, sizeof(line), file)) {
                    if (strcmp(line, "----------------------------------------\n") == 0) {
                        fprintf(tempFile, "%s", line);
                        break;
                    }
                }
            } else {
                fputs(line, tempFile);
            }
        } else {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student with Roll Number %d updated successfully.\n", rollNumber);
    } else {
        printf("Student with Roll Number %d not found.\n", rollNumber);
    }
}
