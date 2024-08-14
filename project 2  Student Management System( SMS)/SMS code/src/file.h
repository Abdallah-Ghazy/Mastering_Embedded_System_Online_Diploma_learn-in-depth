/*
 * file.h
 *
 *  Created on: Aug 14, 2024
 *      Author: Abdallah Ghazy
 */

#ifndef FILE_H_
#define FILE_H_
Status WriteStudentToFile(const Registers *student, const char *filename);
Status ReadStudentsFromFile(const char *filename);
Status DetailsfromFile(const char *filename);
void SearchByRollNumber(int rollNumber);
int GetLastStudentID(const char *filename);
void SearchByFirstName(const char *firstName);
#define MAX_LINE_LENGTH 100
#define MAX_NAME_LENGTH 30
void StudentsRegisteredinCourse(int CourseID);
void CountOfStudents();
void FDeleteStudent(int rollNumber);
void F_UpdateStudent(int rollNumber, const char* newFirstName, const char* newLastName, float newGPA, const char* newEmail);
#endif /* FILE_H_ */
