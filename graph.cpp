#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <iostream>

pNODE *createGraph(int n){
    pNODE *ADJ = new pNODE[n]; //allocate array of pointers for adjacency list
    for (int i = 0; i < n; i++){
        ADJ[i] = nullptr; //initialize each pointer to nullptr (empty list)
    }
    return ADJ;
}

void destroyGraph(pNODE *ADJ, int n){
    if (ADJ == nullptr) return; //null check to prevent dereferencing null pointer

    for (int i = 0; i < n; i++){
        pNODE current = ADJ[i];
        while (current != nullptr){
            pNODE temp = current; //store current node to delete
            current = current->next; //move to next node before deleting
            delete temp; //free memory of current node
        }
    }
    delete[] ADJ; //free memory of adjacency list array
}


//Helper function to add edge to adjacency list, insertAtRear == 1 means add at end of list, 0 means add at front of list
void addEdge(pNODE *ADJ, int edgeIndex, int u, int v, double w, int insertAtRear){
    if (ADJ == nullptr) return; //null check to prevent dereferencing null pointer

    pNODE newNode = new NODE;
    newNode->index = edgeIndex;
    newNode->u = u;
    newNode->v = v;
    newNode->w = w;
    newNode->next = nullptr;

    if (ADJ[u] == nullptr) {
        ADJ[u] = newNode; //first edge for vertex u
    } else {
        if (insertAtRear) {
            pNODE current = ADJ[u];
            while (current->next != nullptr) {
                current = current->next; //traverse to end of list
            }
            current->next = newNode; //add new node at the end
        } else {
            newNode->next = ADJ[u]; //insert at front of list
            ADJ[u] = newNode; //update head of list to new node
        }
    }
};

//PrintADJ command
void printGraph(pNODE *ADJ, int n){
    if (ADJ == nullptr) {
        std::cerr << "Error: adjacency list is NULL\n";
        return;
    }

    for (int i = 0; i < n; i++){
        std::cout << "Vertex " << i << ":";
        pNODE current = ADJ[i];
        while (current != nullptr){
            std::cout << " -> (v" << current->v << ", w=" << current->w << ")";
            current = current->next;
        }
        std::cout << "\n";
    }
};


//helper function to initialize vertices for Dijkstra's algorithm
void initializeSingleSource(pVERTEX *V, int n, int source){
    if (V == nullptr) return; //null check to prevent dereferencing null pointer

    for (int i = 0; i < n; i++){
        V[i]->key = std::numeric_limits<double>::infinity(); //initialize all keys to infinity
        V[i]->pi = -1; //initialize all predecessors to -1 (no predecessor)
        V[i]->color = WHITE; //initialize all vertices as unvisited
    }
    V[source]->key = 0.0; //distance to source vertex is 0
}


//Dijkstra's algorithm implementation
void dijkstra(pVERTEX *V, pNODE *ADJ, int n, int source, int destination, pHEAP pHeap){
    initializeSingleSource(V, n, source); //initialize vertices for Dijkstra's algorithm

    for (int i = 0; i < n; i++){
        insertElement(pHeap, V[i]); //insert all vertices into the heap
    }

    while (pHeap->size > 0){
        pVERTEX u = extractMin(pHeap); //get vertex with smallest key value
        if (u->index == destination) break; //stop if we reached the destination

        pNODE current = ADJ[u->index];
        while (current != nullptr){
            pVERTEX v = V[current->v];
            double alt = u->key + current->w; //calculate alternative path length
            if (alt < v->key){ //if alternative path is shorter
                v->pi = u->index; //update predecessor
                decreaseKey(pHeap, v, alt); //update key value in heap
            }
            current = current->next; //move to next adjacent edge
        }
    }
};


//PrintPath command
void printPath(pVERTEX *V, int source, int destination, pSTACK pStack){
    if (V == nullptr || pStack == nullptr) return; //null check to prevent dereferencing null pointer

    int current = destination;
    while (current != -1){
        push(pStack, current); //push vertex index onto stack
        current = V[current]->pi; //move to predecessor vertex
    }

    std::cout << "Shortest path from vertex " << source << " to vertex " << destination << ": ";
    while (!isEmpty(pStack)){
        int vertexIndex = pop(pStack);
        std::cout << vertexIndex;
        if (!isEmpty(pStack)) std::cout << " -> ";
    }
    std::cout << "\n";
};


//PrintLength command
void printLength(pVERTEX *V, int source, int destination){
    if (V == nullptr) return; //null check to prevent dereferencing null pointer

    double length = V[destination]->key;
    if (length == std::numeric_limits<double>::infinity()){
        std::cout << "No path from vertex " << source << " to vertex " << destination << "\n";
    } else {
        std::cout << "Shortest path length from vertex " << source << " to vertex " << destination << ": " << length << "\n";
    }
};

