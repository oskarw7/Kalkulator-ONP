#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10 // największa liczba znaków dla int'a

typedef struct ONPString {
    char* string;
    unsigned int lenght;
    unsigned int capacity;
} ONPString;

typedef struct CharNode {
    char token[MAX_SIZE];
    CharNode* previous;
} CharNode;

typedef struct IntNode {
    int token;
    IntNode* previous;
} IntNode;

void push(IntNode** top, int token){
    IntNode* new_node = (IntNode*)malloc(sizeof(IntNode));
    new_node->token = token;
    new_node->previous = *top;
    *top = new_node;
}

int pop(IntNode** top){
    IntNode* temp;
    temp = *top;
    int token = temp->token;
    *top = (*top)->previous;
    free(temp);
    return token;
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

void push(CharNode** top, char* token){
    CharNode* new_node = (CharNode*)malloc(sizeof(CharNode));
    //strcpy(new_node->token, token);
    int i=0;
    while(token[i]!='\0'){
        new_node->token[i] = token[i];
        i++;
    }
    while(i<MAX_SIZE){
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

void print_stack(CharNode* top){ // do usunięcia
    while(top!= nullptr) {
        printf("%s ", top->token);
        top = top->previous;
    }
}

void free_stack(CharNode** top){
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

int length(char* s){
    int i=0;
    while(s[i]!='\0')
        i++;
    return i;
}

void append_string(ONPString* onp, char* str){
    int str_lenght = length(str);
    if(onp->lenght!=0){
        onp->lenght += str_lenght + 1;
        if(onp->lenght >= onp->capacity){
            onp->capacity += MAX_SIZE;
            onp->string = (char*)realloc(onp->string, onp->capacity);
            allocation_error(onp->string);
        }
        //onp->string = strcat(onp->string, " ");
        //onp->string = strcat(onp->string, str);
        onp->string[onp->lenght-str_lenght-1] = ' ';
        for(int i=0; i<=str_lenght; i++){
            onp->string[onp->lenght - str_lenght + i] = str[i];
        }
    }
    else {
        onp->lenght += str_lenght;
        if (onp->lenght >= onp->capacity) {
            onp->capacity += MAX_SIZE;
            onp->string = (char *) realloc(onp->string, onp->capacity);
            allocation_error(onp->string);
        }
        for (int i = 0; i < str_lenght; i++) {
            onp->string[onp->lenght - str_lenght + i] = str[i];
        }
    }
    onp->string[onp->lenght] = '\0';
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
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case 'N':
            return 3;
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

void find_parentheses(CharNode**  top, ONPString* onp){ // sprawdzić działanie (zmiana dla przecinka)
    while((*top)->token[0]!='('){
        //onp = add_strings(onp, (*top)->token);
        append_string(onp, (*top)->token);
        pop(top);
    }

}

int convert_number(char* token){
    int num=0, j=1;
    for(int i= length(token)-1; i>=0; i--){
        int digit = token[i] - '0';
        num += digit*j;
        j*=10;
    }
    return num;
}

int count(int a, int b, char o){ // jesli a=0 i o=/, nie wywoluj funkcji
    switch(o){
        case '+':
            return b+a;
        case '-':
            return b-a;
        case '*':
            return b*a;
        case '/':
            return b/a;
    }
    return 0;
}

void convert_infix(CharNode** top, ONPString* onp){
    char token[MAX_SIZE] = "";
    while(token[0]!='.'){
        scanf("%s", token);

        if(token[0]>='0' && token[0]<='9'){
            //onp = add_strings(onp, token);
            append_string(onp, token);
        }
        else if(isOperator(token[0])){
            if(*top == nullptr || token[0] == 'N' || precendence((*top)->token[0]) < precendence(token[0]))
                push(top, token);
            else if(token[0] != 'N'){
                while(*top!=nullptr && (*top)->token[0]!='(' && precendence((*top)->token[0])>=precendence(token[0])){
                    //onp = add_strings(onp, (*top)->token);
                    append_string(onp, (*top)->token);
                    pop(top);
                }
                push(top, token);
            }
        }
        else if(isFunction(token) || token[0]=='('){
            if(token[0]=='M')
                token[3]='1';
            push(top, token);
        }
        else if(token[0]==')'){
            //onp = find_parentheses(top, onp);
            find_parentheses(top, onp);
            pop(top);
            if((*top)!=NULL && isFunction((*top)->token)) {
                //onp = add_strings(onp, (*top)->token);
                append_string(onp, (*top)->token);
                pop(top);
            }
        }
        else if(token[0]==','){
            //onp = find_parentheses(top, onp);
            find_parentheses(top, onp);
            char* temp = (*top)->previous->token;
            if(temp!=NULL && (*top)->token[0]=='('){
                if(temp[0]=='M'){
                    //int num = temp[3] - '0';
                    //num++;
                    //temp[3] = num + '0';
                    int j=1, num=0, digit, digits=0;
                    for(int i=MAX_SIZE-1; i>=3; i--){
                        if(temp[i]!='\0') {
                            digit = temp[i] - '0';
                            num += digit * j;
                            j*=10;
                            if(digits==0 && temp[3]=='9' && temp[4]=='\0')
                                digits++;
                            digits++;
                        }
                    }
                    num++;
                    for(int i=3+digits-1; i>=3; i--){
                        temp[i] = num%10 + '0'; //gdy liczba wynosi 9, to digits=1, a nie 2, wiec wychodzi 0 w modulo
                        num/=10;
                    }
                }
            }
        }
        else if(token[0]=='.'){
            while(*top!= nullptr){
                //onp = add_strings(onp, (*top)->token);
                append_string(onp, (*top)->token);
                pop(top);
            }
        }

        if(token[0]!='.')
            memset(token, '\0', sizeof(token));
    }
}

void count_postfix(char** onp){
    IntNode* top = nullptr;
    char* token;
    token = strtok(*onp, " ");
    while(token != NULL){
        if(token[0]>='0' && token[0]<='9'){
            push(&top, convert_number(token));
        }
        else if(isOperator(token[0])){
            printf("%c ", token[0]);
            print_stack(top);
            int a = pop(&top);
            if(token[0]=='N'){
                push(&top, -1*a);
            }
            else {
                if(token[0]=='/' && a==0){
                    printf("ERROR\n");
                    return;
                }
                int b = pop(&top);
                int result = count(a, b, token[0]);
                push(&top, result);
            }
        }
        else if(token[0]=='I'){
            printf("%s ", token);
            print_stack(top);
            int c = pop(&top);
            int b = pop(&top);
            int a = pop(&top);
            int result = (a>0) ? b : c;
            push(&top, result);
        }
        else if(token[0]=='M'){
            printf("%s ", token);
            print_stack(top);
            int j=1, k=3, num=0, digit, digits=0;
            while(token[k]!='\0'){
                digits++;
                k++;
            }
            for(int i=3+digits-1; i>=3; i--){
                if(token[i]!='\0') {
                    digit = token[i] - '0';
                    num += digit * j;
                    j *= 10;
                }
            }
            if(token[1]=='A'){
                int max = pop(&top), temp;
                for(int i=1; i<num; i++){
                    temp = pop(&top);
                    if(max<temp)
                        max = temp;
                }
                push(&top, max);
            }
            if(token[1]=='I'){
                int min = pop(&top), temp;
                for(int i=1; i<num; i++){
                    temp = pop(&top);
                    if(min>temp)
                        min = temp;
                }
                push(&top, min);
            }
        }
        token = strtok(NULL, " ");
    }
    print_stack(top);
    free_stack(&top);
}


int main() {
    CharNode* top = nullptr;

    ONPString onp;
    onp.string = (char*)malloc(1);
    onp.string[0] = '\0';
    onp.lenght = 0;
    onp.capacity = 1;

    //char* onp = (char *)malloc(1);
    //strcpy(onp, "");

    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        convert_infix(&top, &onp);
        print_string(onp.string);
        printf("\n");

        count_postfix(&onp.string);

        memset(onp.string, '\0', strlen(onp.string));
        onp.lenght = 0;
        onp.capacity = 1;
    }

    free(onp.string);
    free_stack(&top);

    return 0;
}