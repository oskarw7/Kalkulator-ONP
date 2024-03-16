#ifndef CHARSTACK_H
#define CHARSTACK_H

#include <stdlib.h>

#define CHAR_TOKEN_SIZE 6 // maksymalna wielkość tokenu + 1 dla \0

// struktura repreztująca węzeł stosu c-style string'ów
typedef struct CharNode {
    char token[CHAR_TOKEN_SIZE];
    CharNode* previous;
} CharNode;

// dodaje token do stosu
void push(CharNode** top, const char* token);

// zdejmuje token ze stosu
void pop(CharNode** top);

// usuwa stos, zwalnia pamięć
void free_stack(CharNode** top);

#endif