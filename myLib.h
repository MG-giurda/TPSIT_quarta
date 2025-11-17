// modo semplice per fare solo una volta gli include
#ifndef MYLIB_H // se non definito MYLIB_H allora prendi in considerazione tutto quello che è qua dentro 
#define MYLIB_H 

#include <stdio.h>
#include <string.h>
#include <errno.h> // contiene variabile globale errno per dirmi gli errori 
#include <stdlib.h>

#define MAX_STRING_LENGTH 256 // non è una costante ma è un simbolo

void errore(char* s, int n);
char* readLine(FILE* f);
char** splitString(char* s, char delimiter);
void disposeStringArray(char** arr);
int randomRange(int min, int max);

// RIMOSSO: #include "myLib.c"

#endif // MYLIB_H