#include "CharStack.h"

void push(CharNode** top, const char* token){
    CharNode* new_node = (CharNode*)malloc(sizeof(CharNode));
    int i=0;
    while(token[i]!='\0'){
        new_node->token[i] = token[i];
        i++;
    }
    while(i<TOKEN_SIZE){
        new_node->token[i]='\0';
        i++;
    }
    new_node->previous = *top;
    *top = new_node;
}

void pop(CharNode** top){
    CharNode* temp;
    temp = *top;
    *top = (*top)->previous;
    free(temp);
}

void free_stack(CharNode** top){
    while(*top!= nullptr){
        pop(top);
    }
}