//  myLib.c
// implementazione di ciò che è implementato in myLib.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include "myLib.h"

void errore(char* s, int n) {
    printf("Errore %d in %s (%s) \n (exiting with error level %d)\n", errno, s, strerror(errno), n);
    exit(n);
}

char* readLine(FILE* f) {
    char buffer[MAX_STRING_LENGTH];
    int i;
    for(i = 0;
        ((buffer[i]=fgetc(f))!='\n') && (buffer[i]!=EOF);
        i++) { }  
    buffer[i] = '\0';
    return (i==0)? NULL: strdup(buffer);
}

// ATTENZIONE: Altera la stringa originale con strtok()
char** splitString(char* s, char separator) {
    char** tokens = NULL; // token = vuoto
    char delimiter[2] = {separator, '\0' }; // separatore pk ad strtok serve una stringa all'ora noi la creiamo
    // delimiter è una stringa 
    // separator è un carattere
    int count = 0;
    char* token = strtok(s, delimiter); // ci restituisce l'indirizzo della sottostringa
    while(token != NULL) { // utilizziamo while ma fuori con lettura fuori ciclo
        // realloc(): come malloc(), ma rialloca la memoria copiando i vecchi dati
        tokens = realloc(tokens, sizeof(char*) * (count + 1)); // 
        tokens[count] = strdup(token);//ci mette dentro la prima sottostringa
        count++;
        token = strtok(NULL, delimiter); // ma sta volta gli passiamo NULL pk è statefull e quindi tiene i dati salvati e lui non ripartirà più dalla prima ma dalla seconda
    }
    tokens = realloc(tokens, sizeof(char*) * (count + 1)); // metto +1 pk devo allocare anche il NULL
    tokens[count] = NULL; // Terminatore cioè il tappo per la fine del vettore
    return tokens;
}

void disposeStringArray(char** arr) { // funzione da toglierli dalla memoria RAM per non rischiare la memory leak
    for(char** temp = arr; *temp; temp++) { 
        // *temp --> quello che è puntato da temp è diverso da NULL pk almeno se arriva a fine programma si stoppa pk legge NULL
        free(*temp); // dealloca
        // dealloco all'infinito finchè non arriverò a NULL e quindi *temp sarà = a 0 quindi il for finirà
    }
    free(arr); // dealloco tutto 
}

int randomRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}
// seed numero del processo a con cui stiamo lavorando