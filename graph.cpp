#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <cfloat>
#include <iostream>
#include <iomanip>

pNODE *createGraph(int n){
    pNODE *ADJ = new pNODE[n + 1]; //allocate array of pointers for adjacency list using 1-based indexing
    for (int i = 0; i <= n; i++){
        ADJ[i] = nullptr; //initialize each pointer to nullptr (empty list)
    }
    return ADJ;
}

void destroyGraph(pNODE *ADJ, int n){
    if (ADJ == nullptr) return;

    for (int i = 1; i <= n; i++){
        pNODE current = ADJ[i];
        while (current != nullptr){
            pNODE temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] ADJ;
}
//C:\Users\Megan Pierce\Projects\CSE310_P03\graph.cpp

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
    if(ADJ == nullptr) return; //null check 

    //print adjacency list using 1-based indexing
    for (int i = 1; i <= n; i++){
        std::cout << "ADJ[" << i << "]:";
        pNODE current = ADJ[i];
        while (current != nullptr){
            std::cout << "-->["<<current->u<<" "<<current->v<<": "<<std::fixed<<std::setprecision(2)<<current->w<<"]";
            current = current->next; //move to next edge in list
        }
        std::cout << "\n";
    }
};


//helper function to initialize vertices for Dijkstra's algorithm
void initializeSingleSource(pVERTEX *V, int n, int source){
    if (V == nullptr) return; //null check to prevent dereferencing null pointer
    //initialize vertices using 1-based indexing
    for (int i = 1; i <= n; i++){
        V[i]->index = i; //set vertex index
        V[i]->key = DBL_MAX; //initialize all keys to infinity
        V[i]->pi = -1; //initialize all predecessors to -1 (no predecessor)
        V[i]->color = WHITE; //initialize all vertices as unvisited
        V[i]->position = 0; //initialize all vertices as not in heap (position 0)
    }
    V[source]->key = 0.0; //distance to source vertex is 0
}


//Dijkstra's algorithm implementation
/*spec says:
1. initialize all vertices
2. create empty heap
3. set source key to 0
4. insert source only
5. when a white neighbor is discovered, insert it
6. when a gray neighbor improves call DecreaseKey */
void dijkstra(pVERTEX *V, pNODE *ADJ, int n, int source, int destination, pHEAP pHeap){
    initializeSingleSource(V, n, source);

    pHeap->size = 0;

    V[source]->color = GRAY;
    insertElement(pHeap, V[source]);

    while (pHeap->size > 0){
        pVERTEX u = extractMin(pHeap);

        if (destination != -1 && u->index == destination) break;

        pNODE current = ADJ[u->index];

        while (current != nullptr){
            pVERTEX v = V[current->v];
            double alt = u->key + current->w;

            if (v->color == WHITE){
                v->color = GRAY;
                v->key = alt;
                v->pi = u->index;
                insertElement(pHeap, v);
            }
            else if (v->color == GRAY && alt < v->key){
                v->pi = u->index;
                decreaseKey(pHeap, v, alt);
            }

            current = current->next;
        }

        u->color = BLACK;
    }
};


//PrintPath command
/*Formatting not currently in spec, should look like:
The shortest path from 1 to 3 is:
[1: 0.00]-->[4: 5.00]-->[2: 8.00]-->[3: 9.00].*/
void printPath(pVERTEX *V, int source, int destination, pSTACK pStack){
    if (V == nullptr || pStack == nullptr) return; //null check to prevent dereferencing null pointer

    if (V[destination]->key == DBL_MAX){
        std::cout << "There is no path from " << source << " to " << destination << ".\n";
        return;
    }

    int current = destination;
    while (current != -1){
        push(pStack, current);
        current = V[current]->pi;
    }

    std::cout << "The shortest path from " << source << " to " << destination << " is:\n";

    while (!isEmpty(pStack)){
        int v = pop(pStack);
        std::cout << "[" << v << ":" << std::setw(8)
          << std::fixed << std::setprecision(2)
          << V[v]->key << "]";
        if (!isEmpty(pStack)){
            std::cout << "-->";
        }
    }
    std::cout << ".\n";
};


//PrintLength command
void printLength(pVERTEX *V, int source, int destination){
    if (V == nullptr) return;

    if (V[destination]->key == DBL_MAX){
        std::cout << "There is no path from " << source << " to " << destination << ".\n";
    } else {
        std::cout << "The length of the shortest path from "<< source << " to " << destination << " is: "<< std::setw(8) << std::fixed << std::setprecision(2)<< V[destination]->key << "\n";
    }
};

