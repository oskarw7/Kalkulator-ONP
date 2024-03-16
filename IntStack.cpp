#include "IntStack.h"

void push(IntNode** top, int token){
    IntNode* new_node = (IntNode*)malloc(sizeof(IntNode));
    new_node->token = token;
    new_node->previous = *top;
    *top = new_node;
}

int pop(IntNode** top){
    IntNode* temp;
    temp = *top;
    int popped_token = temp->token;
    *top = (*top)->previous;
    free(temp);
    return popped_token;
}

void print_stack(IntNode* top){
    while(top != nullptr) {
        printf("%d ", top->token);
        top = top->previous;
    }
    printf("\n");
}

void free_stack(IntNode** top){
    while(*top!= nullptr){
        pop(top);
    }
}