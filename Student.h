#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    char* name;
    int age;
    float grade;
} Student;

#define MAX_STRING_LENGTH 256

Student* createStudent(char* name, int age, float grade); 
void setName(Student* student, char* name);// passaggio per referenza pk devo poter cambiare il nome 
char* getName(Student student);
void setAge(Student* student, int age);
int getAge(Student student);
void setGrade(Student* student, float grade);
float getGrade(Student student);
void disposeStudent(Student* student);
void printStudent(Student student);
char* studentToCSV(Student student);
Student* createFromCSV(char* csvLine);

// RIMOSSO: #include "Student.c"

#endif // STUDENT_H