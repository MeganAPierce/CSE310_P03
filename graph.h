#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"

pNODE *createGraph(int n); 
void destroyGraph(pNODE *ADJ, int n); 

void addEdge(pNODE *ADJ, int edgeIndex, int u, int v, double w, int insertAtRear);
void printGraph(pNODE *ADJ, int n);
void initializeSingleSource(pVERTEX *V, int n, int source);
void dijkstra(pVERTEX *V, pNODE *ADJ, int n, int source, int destination, pHEAP pHeap);
void printPath(pVERTEX *V, int source, int destination, pSTACK pStack);
void printLength(pVERTEX *V, int source, int destination);
#endif