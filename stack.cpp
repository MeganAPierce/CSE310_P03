#include "stack.h"
#include <iostream>

pSTACK createStack(int capacity){
    pSTACK pStack = new STACK;
    pStack->capacity = capacity;
    pStack->top = -1; //initialize top to -1 to indicate empty stack
    pStack->S = new int[capacity]; //allocate array for stack elements
    return pStack;
}

void destroyStack(pSTACK pStack){
    if(pStack != nullptr){
        delete[] pStack->S; //free array memory to prevent memory leaks
        delete pStack; //free stack structure memory to prevent memory leaks
    }
    pStack = nullptr; 
}

//pushes vertex index onto the stack, does nothing if stack is full or an invalid pointer is passed
void push(pSTACK pStack, int vertexIndex){
    if (pStack == nullptr) return; //null check (prevent dereferencing null pointer)
    if (pStack->top >= pStack->capacity - 1) return; //full-stack check (prevent overflow)

    pStack->top++; //increment top  
    pStack->S[pStack->top] = vertexIndex; //add vertex index to top of stack
}

//pops top vertex index from stack and returns it, returns -1 if stack is empty or invalid input
int pop(pSTACK pStack){
    if (pStack == nullptr || pStack->top < 0) return -1; //invalid input or stack is empty

    int vertexIndex = pStack->S[pStack->top]; //get vertex index at top of stack
    pStack->top--; //decrement top to remove element from stack
    return vertexIndex;
}

//1 == true, 0 == false
int isEmpty(pSTACK pStack){
    if (pStack == nullptr) return 1; //invalid input, treat as empty stack
    return (pStack->top < 0); //returns 1 if stack is empty, 0 otherwise
}