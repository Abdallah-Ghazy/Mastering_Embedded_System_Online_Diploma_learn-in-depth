/*
 * SMS.h
 *
 *  Created on: Aug 14, 2024
 *      Author: Abdallah Ghazy
 */

#ifndef SMS_H_
#define SMS_H_

typedef struct {
	int StudentID;
	int RollNumber;
	char FirstName[30];
	char LastName[30];
	float GPA;
	char Email[100];
} Student;

typedef struct {
	int CourseID;
	char CourseName[100];
} Course;

typedef struct {
	Student Student;
	Course Course;
	const char *RegistrationDate;
} Registers;

typedef enum {
    SUCCESS = 0,
    FILE_ERROR,
    STUDENT_NOT_FOUND,
    INVALID_INPUT,
    STUDENT_EXISTS,
    OTHER_ERROR
} Status;

// Function prototypes
Status displayMenu();
Status AddStudentDetailsfromFile(void);
Status AddStudentDetailsManually(void);
Status FindStudentByGivenRollNumber(void);
Status FindStudentByGivenFirstName(void);
Status FindStudentsRegisteredinCourse(void);
Status CountStudents(void);
Status DeleteStudent(void);
Status UpdateStudent(void);
Status Exit(void);
void ExecuteOption(void);
void PrintStudentDetails(const Registers *student);

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

#define MAX_FILENAME_LENGTH 100


#include "file.h"
#endif /* SMS_H_ */
