#include "ONPString.h"

void allocation_error(const char* s1){
    if (s1 == nullptr) {
        printf("Allocating memory failed");
        exit(1);
    }
}

int length(const char* s){
    int i=0;
    while(s[i]!='\0')
        i++;
    return i;
}

void append_string(ONPString* onp, const char* str){
    int str_lenght = length(str), isEmpty=0;
    if(onp->lenght==0)
        isEmpty=1;

    onp->lenght += str_lenght + (isEmpty==0 ? 1 : 0);

    if(onp->lenght >= onp->capacity){
        onp->capacity += INT_TOKEN_SIZE;
        onp->string = (char*)realloc(onp->string, onp->capacity);
        allocation_error(onp->string);
    }

    if(isEmpty==0)
        onp->string[onp->lenght-str_lenght-1] = ' ';
    for(int i=0; i<str_lenght; i++)
        onp->string[onp->lenght - str_lenght + i] = str[i];
    onp->string[onp->lenght] = '\0';
}

void print_string(const char* string){
    int i=0;
    while(string[i]!='\0'){
        printf("%c", string[i]);
        i++;
    }
}