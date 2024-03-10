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

void allocation_error(char* s1){
    if (s1 == NULL) {
        printf("Allocating memory failed");
        exit(1);
    }
}

char* add_strings(char* s1, char* s2){ // usunąć ostatnią spację
    unsigned int size = strlen(s1) + strlen(s2);
    if(strcmp(s1, "")==0) {
        s1 = (char *) realloc(s1, size + 1); // plus \0
        allocation_error(s1);
    }
    else{
        s1 = (char *) realloc(s1, size + 2); // plus \0 i spacja
        allocation_error(s1);
        strcat(s1, " ");
    }
    strcat(s1, s2);
    return s1;
}

void print_string(char* string){
    int i=0;
    while(string[i]!='\0'){
        printf("%c", string[i]);
        i++;
    }
}

int precendence(char c){
    switch(c){
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        case 'N':
            return 3;
            break;
    }
    return 0;
}

int isOperator(char c) {
    char operators[] = {'+', '-', '*', '/', 'N'};
    for (char elem: operators) {
        if (c == elem)
            return 1;
    }
    return 0;
}

int isFunction(char* c){
    char functions[][MAX_SIZE] = {"MIN", "MAX", "IF", "N"};
    for(char* elem : functions){
        if(strncmp(c, elem, 3)==0)
            return 1;
    }
    return 0;
}

char* find_parentheses(Node**  top, char* onp){ // sprawdzić działanie (zmiana dla przecinka)
    while((*top)->token[0]!='('){
        onp = add_strings(onp, (*top)->token);
        pop(top);
    }
    return onp;
}

char* convert_infix(Node** top, char* onp){
    char token[MAX_SIZE] = "";
    while(token[0]!='.'){
        scanf("%s", token);

        if(token[0]>='0' && token[0]<='9'){
            onp = add_strings(onp, token);
        }
        else if(isOperator(token[0])){
            if(*top == nullptr || token[0] == 'N' || precendence((*top)->token[0]) < precendence(token[0]))
                push(top, token);
            else if(token[0] != 'N'){
                while(*top!=nullptr && (*top)->token[0]!='(' && precendence((*top)->token[0])>=precendence(token[0])){
                    onp = add_strings(onp, (*top)->token);
                    pop(top);
                }
                push(top, token);
            }
        }
        else if(isFunction(token) || token[0]=='('){
            if(strcmp(token, "MAX")==0 | strcmp(token, "MIN")==0)
                token[3]='1';
            push(top, token);
        }
        else if(token[0]==')'){
            onp = find_parentheses(top, onp);
            pop(top);
            if((*top)!=NULL && isFunction((*top)->token)) {
                onp = add_strings(onp, (*top)->token);
                pop(top);
            }
        }
        else if(token[0]==','){
            onp = find_parentheses(top, onp);
            char* temp = (*top)->previous->token;
            if(temp!=NULL && (*top)->token[0]=='('){
                if(strncmp(temp, "MAX", 3) == 0 || strncmp(temp, "MIN", 3) == 0){
                    int num = temp[3] - '0';
                    num++;
                    temp[3] = num + '0';
                }
            }
        }
        else if(token[0]=='.'){
            while(*top!= nullptr){
                onp = add_strings(onp, (*top)->token);
                pop(top);
            }
        }

        if(token[0]!='.')
            memset(token, '\0', sizeof(token));
    }
    return onp;
}

void count_postfix(Node** top, char* onp){
    char* token;
    token = strtok(onp, " ");
    while(token != NULL){
        

        token = strtok(NULL, " ");
    }
}


int main() {
    Node* top = nullptr;
    char* onp = (char *)malloc(1);
    strcpy(onp, "");

    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        onp = convert_infix(&top, onp);
        print_string(onp);
        printf("\n");

        count_postfix(&top, onp);

        memset(onp, '\0', strlen(onp));
    }

    free(onp);
    free_stack(&top);

    return 0;
}