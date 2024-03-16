#ifndef ONPSTRING_H
#define ONPSTRING_H

#include <stdlib.h>
#include <stdio.h>

#define INT_TOKEN_SIZE 11 // największa liczba znaków dla int'a + 1 dla \0

// struktura przechowująca wyrażenie ONP
typedef struct ONPString {
    char* string;
    unsigned int lenght;
    unsigned int capacity;
} ONPString;

// sprawdza, czy alokacja pamięci się powiodła
void allocation_error(const char* s1);

// zwraca długość stringa
int length(const char* s);

// dodaje c-style stringa do wyrażenia ONP
void append_string(ONPString* onp, const char* str);

void print_string(const char* string);

#endif
