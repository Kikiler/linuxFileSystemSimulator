//
// Created by Killian Evouna on 10/11/2025.
//
#include "stack.h"

stack* initStack(int size) {
    if (size <= 0 ) {
        fprintf(stderr, "Error: stack size must be greater than 0\n");
        exit(-1);
    }
    stack* myStack = malloc(sizeof(stack));
    myStack->content = malloc(size * sizeof(char*));
    myStack->size = size;
    myStack->indexOfNext = 0;

    return myStack;
}

void pileUp(stack* myStack, const char* str) {
    if (myStack == NULL) {
        fprintf(stderr, "Error: myStack is null\n");
        exit(-1);
    }
    if (myStack->size/2 <= myStack->indexOfNext) {
        char** resizedArr = malloc(2* myStack->size * sizeof(char*));
        for (int i = 0; i < myStack->indexOfNext; i++) {
            resizedArr[i] = myStack->content[i];
        }
        free(myStack->content);
        myStack->content = resizedArr;
        myStack->size = 2*myStack->size;
    }
    myStack->content[myStack->indexOfNext] = strdup(str);
    myStack->indexOfNext++;
}

void destroyStack(stack* myStack) {
    if (myStack == NULL) {
        fprintf(stderr, "Error: myStack is null\n");
        exit(-1);
    }
    for (int i = 0; i < myStack->indexOfNext; i++) {
        free(myStack->content[i]);
    }
    free(myStack->content);
    free(myStack);
}

void printStack(const stack* myStack) {
    if(myStack == NULL){
        fprintf(stderr, "myStack is null");
        exit(-1);
    }
    printf("[ %s", myStack->content[myStack->indexOfNext-1]);
    for(int i = myStack->indexOfNext-2; 0 <= i; i--){
        printf(" -> %s", myStack->content[i]);
    }
    puts(" ]");
}
