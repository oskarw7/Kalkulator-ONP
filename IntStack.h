#ifndef INTSTACK_H
#define INTSTACK_H

#include <stdlib.h>
#include <stdio.h>

// struktura repreztująca węzeł stosu int'ów
typedef struct IntNode {
    int token;
    IntNode* previous;
} IntNode;

// dodaje inta do stosu
void push(IntNode** top, int token);

// zdejmuje inta ze stosu i zwraca go
int pop(IntNode** top);

// wypisuje stos
void print_stack(IntNode* top);

// usuwa stos, zwalnia pamięć
void free_stack(IntNode** top);

#endif