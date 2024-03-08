#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10 // największa liczba znaków dla int'a

typedef struct Node {
    char token[MAX_SIZE];
    Node* previous;
} Node;


void push(Node** top, char* token){
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->token, token);

    new_node->previous = *top;
    *top = new_node;
}

void pop(Node** top){
    Node* temp;
    temp = *top;
    *top = (*top)->previous;
    free(temp);
}

void print_stack(Node* top){
    while(top!= nullptr) {
        printf("%s ", top->token);
        top = top->previous;
    }
}

void free_stack(Node** top){
    while(*top!= nullptr){
        pop(top);
    }
}


int main() {
    Node* top = nullptr;

    print_stack(top);
    free_stack(&top);

    return 0;
}