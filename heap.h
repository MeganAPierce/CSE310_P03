/*Reusing from project 02*/
#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

void printHeap(pHEAP pHeap);

pHEAP createHeap(int capacity);

void destroyHeap(pHEAP pHeap);

void insertElement(pHEAP pHeap, pVERTEX vertex);
pVERTEX extractMin(pHEAP pHeap);
void decreaseKey(pHEAP pHeap, pVERTEX vertex, double newKey);

#endif