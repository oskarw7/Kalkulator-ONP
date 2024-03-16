#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CharStack.h"
#include "IntStack.h"
#include "ONPString.h"

// zwraca priorytet operatora
int precendence(const char c){
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
        default:
            return -1;
    }
}

// sprawdza, czy znak jest operatorem
int isOperator(const char c) {
    char operators[] = {'+', '-', '*', '/', 'N'};
    for (char elem: operators) {
        if (c == elem)
            return 1;
    }
    return 0;
}

// sprawdza, czy ciąg znaków jest funkcją
int isFunction(const char* c){
    char functions[][CHAR_TOKEN_SIZE-2] = {"MIN", "MAX", "IF", "N"};
    for(char* elem : functions){
        if(strncmp(c, elem, 3)==0)
            return 1;
    }
    return 0;
}

// dodaje tokeny ze stosu do ONP do czasu napotkania pasującego nawiasu
void find_parentheses(CharNode**  top, ONPString* onp){
    while((*top)->token[0]!='('){
        append_string(onp, (*top)->token);
        pop(top);
    }
}

// konwertuje c-style stringa na liczbę podczas obliczania wyrażenia ONP
int convert_number(const char* token){
    int num=0, j=1;
    for(int i= length(token)-1; i>=0; i--){
        int digit = token[i] - '0';
        num += digit*j;
        j*=10;
    }
    return num;
}

// zwiększa liczbę o 1 podczas konwersji wyrażenia ONP
void increment_number(char* token){
    int j=1, num=0, digit, digits=0;
    for(int i=CHAR_TOKEN_SIZE-1; i>=3; i--){
        if(token[i]!='\0') {
            digit = token[i] - '0';
            num += digit * j;
            j*=10;
            if(digits==0 && token[3]=='9' && token[4]=='\0')
                digits++;
            digits++;
        }
    }
    num++;
    for(int i=3+digits-1; i>=3; i--){
        token[i] = num%10 + '0';
        num/=10;
    }
}

// wyodrębnia liczbę z tokenu MIN/MAX
int extract_number(const char* token){
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
    return num;
}

int max(IntNode** top, const int num_lenght){
    int max = pop(top);
    for(int i=1; i<num_lenght; i++){
        int temp = pop(top);
        if(max<temp)
            max = temp;
    }
    return max;
}

int min(IntNode** top, const int num_lenght){
    int min = pop(top);
    for(int i=1; i<num_lenght; i++){
        int temp = pop(top);
        if(min>temp)
            min = temp;
    }
    return min;
}

int count(int a, int b, char o){
    switch(o){
        case '+':
            return b+a;
        case '-':
            return b-a;
        case '*':
            return b*a;
        case '/':
            return b/a;
        default:
            return 0;
    }
}

// czyta wyrażenie infiksowe i zamienia je na wyrażenie ONP
void convert_infix(ONPString* onp){
    CharNode* top = nullptr;
    char token[INT_TOKEN_SIZE] = "";
    while(token[0]!='.'){
        scanf("%10s", token);

        if(token[0]>='0' && token[0]<='9')
            append_string(onp, token);
        else if(isOperator(token[0])){
            if(top == nullptr || token[0] == 'N' || precendence(top->token[0]) < precendence(token[0]))
                push(&top, token);
            else if(token[0] != 'N'){
                while(top!=nullptr && top->token[0]!='(' && precendence(top->token[0])>=precendence(token[0])){
                    append_string(onp, top->token);
                    pop(&top);
                }
                push(&top, token);
            }
        }
        else if(isFunction(token) || token[0]=='('){
            if(token[0]=='M')
                token[3]='1';
            push(&top, token);
        }
        else if(token[0]==')'){
            find_parentheses(&top, onp);
            pop(&top);
            if(top!=nullptr && isFunction(top->token)) {
                append_string(onp, top->token);
                pop(&top);
            }
        }
        else if(token[0]==','){
            find_parentheses(&top, onp);
            if(top->token[0]=='(' && top->previous->token[0]=='M')
                    increment_number(top->previous->token);
        }
        else if(token[0]=='.'){
            while(top!=nullptr){
                append_string(onp, top->token);
                pop(&top);
            }
        }
    }
    free_stack(&top);
}

// oblicza wyrażenie ONP
void count_postfix(char** onp){
    IntNode* top = nullptr;
    char* token;
    token = strtok(*onp, " ");
    while(token != nullptr){
        if(token[0]>='0' && token[0]<='9')
            push(&top, convert_number(token));
        else if(isOperator(token[0])){
            printf("%c ", token[0]);
            print_stack(top);
            int a = pop(&top);
            if(token[0]=='N')
                push(&top, -1*a);
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
            int c = pop(&top), b = pop(&top), a = pop(&top);
            push(&top, (a>0) ? b : c);
        }
        else if(token[0]=='M'){
            printf("%s ", token);
            print_stack(top);
            if(token[1]=='A')
                push(&top, max(&top, extract_number(token)));
            else if(token[1]=='I')
                push(&top, min(&top, extract_number(token)));
        }
        token = strtok(nullptr, " ");
    }
    print_stack(top);
    free_stack(&top);
}


int main() {
    ONPString onp;
    onp.string = (char*)malloc(1);
    onp.string[0] = '\0';
    onp.lenght = 0;
    onp.capacity = 1;

    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        convert_infix(&onp);
        print_string(onp.string);
        printf("\n");

        count_postfix(&onp.string);

        memset(onp.string, '\0', length(onp.string));
        onp.lenght = 0;
        onp.capacity = 1;
    }

    free(onp.string);

    return 0;
}