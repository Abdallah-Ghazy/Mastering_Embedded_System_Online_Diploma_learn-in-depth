#include <stdio.h>
#include <string.h>
#include "SMS.h"
#include <string.h>

// Array of function pointers
Status (*SelectOption[])(void) = {
	AddStudentDetailsfromFile,
	AddStudentDetailsManually,
	FindStudentByGivenRollNumber,
	FindStudentByGivenFirstName,
	FindStudentsRegisteredinCourse,
	CountStudents,
	DeleteStudent,
	UpdateStudent,
	Exit
};
int flag = 1;
char *FileName = "students.txt";

void PrintStudentDetails(const Registers *student) {
	printf(BOLD CYAN "Student Details:\n" RESET);
	printf(BOLD GREEN "Roll Number: " RESET "%d\n",student->Student.RollNumber);
	printf(BOLD GREEN "First Name: " RESET "%s\n", student->Student.FirstName);
	printf(BOLD GREEN "Last Name: " RESET "%s\n", student->Student.LastName);
	printf(BOLD GREEN "GPA: " RESET "%.2f\n", student->Student.GPA);
	printf(BOLD GREEN "Email: " RESET "%s\n", student->Student.Email);
	printf(BOLD GREEN "Course ID: " RESET "%d\n", student->Course.CourseID);
	printf(BOLD GREEN "Course Name: " RESET "%s\n", student->Course.CourseName);
	printf(BOLD GREEN "Registration Date: " RESET "%s\n",student->RegistrationDate);

}



void ExecuteOption(void) {
	int Option;
	fflush(stdout);
	scanf("%d", &Option);
	printf(BOLD BLUE "========================================\n" RESET);

	if (Option >= 1 && Option <= 9) {
		SelectOption[Option - 1]();
	} else {
		printf("Invalid option selected.\n");
	}
}

Status displayMenu() {
    printf(BOLD BLUE "****************************************\n" RESET);
    printf(BOLD BLUE "*                                      *\n" RESET);
    printf(BOLD YELLOW "*  --- Student Management System ---   *\n" RESET);
    printf(BOLD BLUE "*                                      *\n" RESET);
    printf(BOLD BLUE "****************************************\n" RESET);
    printf(BOLD BLUE "*                                      *\n" RESET);
    printf(GREEN "*  1. Add Student Details from File    *\n" RESET);
    printf(GREEN "*  2. Add Student Details Manually     *\n" RESET);
    printf(GREEN "*  3. Find the Student by Roll Number  *\n" RESET);
    printf(GREEN "*  4. Find the Student by First Name   *\n" RESET);
    printf(GREEN "*  5. Find Students in a Course        *\n" RESET);
    printf(GREEN "*  6. Count of Students                *\n" RESET);
    printf(GREEN "*  7. Delete a Student                 *\n" RESET);
    printf(GREEN "*  8. Update Student                   *\n" RESET);
    printf(GREEN "*  9. Exit                             *\n" RESET);
    printf(BOLD BLUE "*                                      *\n" RESET);
    printf(BOLD BLUE "****************************************\n" RESET);
    printf(CYAN "Please choose an option (1-9): " RESET);

    return SUCCESS;
}

Status AddStudentDetailsfromFile(void) {
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║" YELLOW "      ----- Welcome! You chose to add student details from a file -----        " RESET "║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");

    char File[MAX_FILENAME_LENGTH];

    printf("  Please enter the name of the file from which you want to load student details.\n");
    printf("  File: ");
    fflush(stdout);

    if (scanf("%255s", File) == 1) {
        if (strstr(File, ".txt") == NULL) {
            strcat(File, ".txt");
        }

        printf("  You have entered the file name: %s\n", File);
        DetailsfromFile(File);
    } else {
        printf("  Error reading the file name.\n");
        return -1;
    }

    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    return SUCCESS;
}




Status AddStudentDetailsManually(void) {
    printf(BOLD YELLOW "══════════════════════════════════════════════════════════════════════════\n" RESET);
    printf(BOLD YELLOW "        ---- Welcome! You chose to add student details manually ----      \n" RESET);
    printf(BOLD YELLOW "══════════════════════════════════════════════════════════════════════════\n\n" RESET);

    Registers student;
    student.Student.RollNumber = GetLastStudentID(FileName) + 1;
    while (getchar() != '\n');

    printf(BOLD GREEN "[1] Please enter the First Name: " RESET);
    fflush(stdout);
    fgets(student.Student.FirstName, sizeof(student.Student.FirstName), stdin);
    student.Student.FirstName[strcspn(student.Student.FirstName, "\n")] = '\0';

    printf(BOLD GREEN "[2] Please enter the Last Name: " RESET);
    fflush(stdout);
    fgets(student.Student.LastName, sizeof(student.Student.LastName), stdin);
    student.Student.LastName[strcspn(student.Student.LastName, "\n")] = '\0';

    printf(BOLD GREEN "[3] Please enter the GPA: " RESET);
    fflush(stdout);
    scanf("%f", &(student.Student.GPA));
    while (getchar() != '\n');

    printf(BOLD GREEN "[4] Please enter the Email: " RESET);
    fflush(stdout);
    fgets(student.Student.Email, sizeof(student.Student.Email), stdin);
    student.Student.Email[strcspn(student.Student.Email, "\n")] = '\0';

    printf(BOLD GREEN "[5] Please enter the Course ID: " RESET);
    fflush(stdout);
    scanf("%d", &(student.Course.CourseID));
    while (getchar() != '\n');

    printf(BOLD GREEN "[6] Please enter the Course Name: " RESET);
    fflush(stdout);
    fgets(student.Course.CourseName, sizeof(student.Course.CourseName), stdin);
    student.Course.CourseName[strcspn(student.Course.CourseName, "\n")] = '\0';

    student.RegistrationDate = __DATE__;

    printf(BOLD YELLOW "----------------------------------------\n" RESET);
    if (WriteStudentToFile(&student, FileName) == SUCCESS) {
        printf(BOLD YELLOW "Student details added successfully!\n" RESET);
        PrintStudentDetails(&student);
    } else {
        printf(BOLD RED "Error adding Student details \n" RESET);
    }
    printf(BOLD YELLOW "----------------------------------------\n" RESET);

    return SUCCESS;
}


Status FindStudentByGivenRollNumber(void) {
    printf(BOLD YELLOW "╔═══════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD YELLOW " ---- Welcome! You chose to find a student by the given roll number ----      \n" RESET);
    printf(BOLD YELLOW "╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

    int RollNumber;
    printf(BOLD GREEN "Please enter the Roll Number for the student: " RESET);
    fflush(stdout);
    scanf("%d", &RollNumber);

    SearchByRollNumber(RollNumber);

    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    return SUCCESS;
}


Status FindStudentByGivenFirstName(void) {
    printf(BOLD YELLOW "╔═══════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD YELLOW "     ---- Welcome! You chose to find a student by the given first name ----       \n" RESET);
    printf(BOLD YELLOW "╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);


    char FirstName[MAX_FILENAME_LENGTH];
    printf(BOLD GREEN "Please enter the First Name for the student: " RESET);
    fflush(stdout);

    if (scanf("%29s", FirstName) == 1) {
        printf(BOLD CYAN "Student: %s\n" RESET, FirstName);
        SearchByFirstName(FirstName);
    } else {
        printf(BOLD RED "Error reading the first name.\n" RESET);
        return -1;
    }

    printf(BOLD BLUE "\n╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);
    return SUCCESS;
}



Status FindStudentsRegisteredinCourse(void) {
	   printf(BOLD YELLOW "╔═══════════════════════════════════════════════════════════════════════════════╗\n" RESET);
	   printf(BOLD YELLOW "      ---- Welcome! You chose to find students registered in a course ----       \n" RESET);
	   printf(BOLD YELLOW "╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

    int CourseID;
    printf(BOLD GREEN "Please enter the Course ID: " RESET);
    fflush(stdout);
    scanf("%d", &CourseID);
    StudentsRegisteredinCourse(CourseID);
    printf(BOLD BLUE "\n╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);


	return SUCCESS;
}



Status CountStudents(void) {
	   printf(BOLD YELLOW "╔═══════════════════════════════════════════════════════════════════════════════╗\n" RESET);
	   printf(BOLD YELLOW "                  ---- Welcome! You chose to count the students ----       \n" RESET);
	   printf(BOLD YELLOW "╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

	CountOfStudents();
    printf(BOLD BLUE "\n╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

	return SUCCESS;
}

Status DeleteStudent(void) {
	   printf(BOLD YELLOW "╔═══════════════════════════════════════════════════════════════════════════════╗\n" RESET);
	   printf(BOLD YELLOW "                ---- Welcome! You chose to delete a student ----       \n" RESET);
	   printf(BOLD YELLOW "╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

    int RollNumber;
    printf(BOLD GREEN "Please enter the Roll Number: " RESET);
    fflush(stdout);
    scanf("%d", &RollNumber);
    FDeleteStudent(RollNumber);

    printf(BOLD BLUE "\n╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

	return SUCCESS;
}

Status UpdateStudent(void) {

	   printf(BOLD YELLOW "╔═══════════════════════════════════════════════════════════════════════════════╗\n" RESET);
	   printf(BOLD YELLOW "      ---- Welcome! You chose to Update students registered in a course ----       \n" RESET);
	   printf(BOLD YELLOW "╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

    Registers student;
    int RollNumber;
    printf(BOLD GREEN "Please enter the Roll Number: " RESET);
    fflush(stdout);
    scanf("%d", &RollNumber);
    while (getchar() != '\n');

    printf(BOLD GREEN "[1] Please enter the First Name: " RESET);
    fflush(stdout);
    fgets(student.Student.FirstName, sizeof(student.Student.FirstName), stdin);
    student.Student.FirstName[strcspn(student.Student.FirstName, "\n")] = '\0';

    printf(BOLD GREEN "[2] Please enter the Last Name: " RESET);
    fflush(stdout);
    fgets(student.Student.LastName, sizeof(student.Student.LastName), stdin);
    student.Student.LastName[strcspn(student.Student.LastName, "\n")] = '\0';

    printf(BOLD GREEN "[3] Please enter the GPA: " RESET);
    fflush(stdout);
    scanf("%f", &(student.Student.GPA));
    while (getchar() != '\n');

    printf(BOLD GREEN "[4] Please enter the Email: " RESET);
    fflush(stdout);
    fgets(student.Student.Email, sizeof(student.Student.Email), stdin);
    student.Student.Email[strcspn(student.Student.Email, "\n")] = '\0';

    printf(BOLD GREEN "[5] Please enter the Course ID: " RESET);
    fflush(stdout);
    scanf("%d", &(student.Course.CourseID));
    while (getchar() != '\n');

    printf(BOLD GREEN "[6] Please enter the Course Name: " RESET);
    fflush(stdout);
    fgets(student.Course.CourseName, sizeof(student.Course.CourseName), stdin);
    student.Course.CourseName[strcspn(student.Course.CourseName, "\n")] = '\0';

    student.RegistrationDate = __DATE__;

    F_UpdateStudent(RollNumber, student.Student.FirstName, student.Student.LastName, student.Student.GPA, student.Student.Email);
	printf(
			BOLD BLUE "\n╚═══════════════════════════════════════════════════════════════════════════════╝\n\n" RESET);

    return SUCCESS;


}



Status Exit(void) {
	printf("\n \n ");
	printf("Exiting the system. Goodbye!\n");
	flag = 0;
	return SUCCESS;
}
