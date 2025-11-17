/* studentsCollection.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "myLib.h" 
#include "Student.h"

Student** loadStudentsFromFile(FILE* f, int* outCount);
void saveStudentsToFile(FILE* file, Student** students);
void disposeStudentArray(Student** students);

int main(int argc, char* argv[]) {
    
    if ((argc != 2) && (argc != 3)) {
        printf("Usage: %s <fileInput> [<fileOutput>]\n", argv[0]);
        return 1;
    }
    
    char* filenameIn = argv[1];
    char* filenameOut = argv[2];
    
    printf("Loading students from file: %s...\n", filenameIn);
    FILE* fileIn = fopen(filenameIn, "r");
    if(fileIn == NULL)  errore("fopen()", 2);
    int studentsCount;
    Student** students = loadStudentsFromFile(fileIn, &studentsCount);
    fclose(fileIn);
    printf("Loaded %d students from %s.\n", studentsCount, filenameIn);

    for(Student** temp = students; *temp; temp++) {
        printStudent(**temp);
    }   

    srand(time(NULL));
    printf("Updating students' ages and grades... ");
    for(Student** temp = students; *temp; temp++) {
        setAge(*temp, getAge(**temp) + 1);
        setGrade(*temp, randomRange(20, 100)/10.0);
    }
    printf("Done.\n");

    if(filenameOut != NULL) {
        
        printf("Saving students to file: %s...\n", filenameOut);
        FILE* fileOut = fopen(filenameOut, "w");
        if(fileOut == NULL)  errore("fopen()", 3);
        saveStudentsToFile(fileOut, students);
        printf("Saved %d students to %s.\n", studentsCount, filenameOut);
        fclose(fileOut);
    }
    
    printf("Disposing students...\n");
    disposeStudentArray(students);

    return 0;
}

Student** loadStudentsFromFile(FILE* f, int* outCount) {
    char* line;
    Student** students = NULL;
    int count = 0;
    
    while((line = readLine(f)) != NULL) {
        Student* student = createFromCSV(line);
        students = realloc(students, sizeof(Student*) * (count + 1));                   
        students[count] = student;
        count++;
        free(line);
    }
    students = realloc(students, sizeof(Student*) * (count + 1));
    students[count] = NULL; // Terminatore
    
    *outCount = count;
    return students;
}

void saveStudentsToFile(FILE* file, Student** students) {
    for(Student** temp = students; *temp; temp++) {
        char* csvLine = studentToCSV(**temp);
        fprintf(file, "%s\n", csvLine);
        free(csvLine);
    }
}

void disposeStudentArray(Student** students) {
    for(Student** temp = students; *temp; temp++) {
        disposeStudent(*temp);
    }
    free(students);
}