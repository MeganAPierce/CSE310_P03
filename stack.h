#ifndef STACK_H
#define STACK_H

#include "data_structures.h" 

pSTACK createStack(int capacity); //creates an empty stack with the specified capacity and returns a pointer to it
void destroyStack(pSTACK pStack); //frees memory allocated for stack 

void push(pSTACK pStack, int vertexIndex); //pushes a vertex index onto stack
int pop(pSTACK pStack); //returns vertex index at the top of the stack 
int isEmpty(pSTACK pStack); //returns 1 if stack is empty, 0 otherwise


#endif