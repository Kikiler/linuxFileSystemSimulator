//
// Created by Killian Evouna on 10/11/2025.
//
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct staticStack {
    char** content;
    int size;
    int indexOfNext;
}
stack;

stack* initStack(int size);

void pileUp(stack* myStack, const char* str);

void destroyStack(stack* myStack);

void printStack(const stack* myStack);

