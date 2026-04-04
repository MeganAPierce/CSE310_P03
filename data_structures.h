#ifndef _data_structures_h
#define _data_structures_h 1

typedef enum { //NEEDED FOR GRAPH TRAVERSAL  
    WHITE, //unvisited
    GRAY, //discovered but not fully explored
    BLACK //fully explored
} COLOR; 

typedef struct TAG_VERTEX {
    int index; //vertex number
    COLOR color; 
    double key; //shortest known path distance
    int pi; //predecessor vertex index, will be -1 if no predecessor
    int position; //position in heap array, will be 0 if not in heap
} VERTEX;

typedef VERTEX *pVERTEX;

typedef struct TAG_NODE{
    int index; //edge index
    int u; //starting vertex index
    int v; //ending vertex index
    double w; //edge weight
    struct TAG_NODE *next; //next edge in adjacency list
} NODE;

typedef NODE *pNODE; //pointer to NODE

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT; //pointer to ELEMENT

typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT *H; //array of pointers to ELEMENT
} HEAP;

typedef HEAP *pHEAP; //pointer to HEAP

typedef struct TAG_STACK {
    int capacity;
    int top;
    int *S; //array of vertex indices
} STACK;

typedef STACK *pSTACK; //pointer to STACK

#endif