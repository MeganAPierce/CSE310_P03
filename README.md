----------OVERVIEW-----------
This program implements a graph-based navigation system that computes shortest paths using Dijkstra’s Algorithm. It supports both directed and undirected graphs, allows dynamic interaction via standard input, and provides efficient shortest path queries.

The system:
-Reads a graph from an input file
-Builds an adjacency list representation
-Computes shortest paths using a min-heap (priority queue)
-Supports interactive commands for querying paths and distances

-----------FEATURES-----------
-Supports both DirectedGraphs and UndirectedGraphs
-Efficient shortest path computation with time complexity of O((m + n) log n)
-Uses:
    -Adjacency list for graph storage
    -Min-heap for Dijkstra's algorithm
    -Stack for path reconstruction
-Strict input validation and memory management
-No memory leaks (all structures are properly destroyed)

--------DATA STRUCTURES--------
        
        VERTEX
typedef struct TAG_VERTEX {
    int index;
    COLOR color;
    double key; //shortest distance from source
    int pi; //predecessor (used for path reconstruction)
    int position;
} VERTEX;

        GRAPH

typedef struct TAG_NODE {
    int u, v;
    double w;
    struct TAG_NODE *next;
} NODE;

        HEAP

typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT *H;
} HEAP;

        STACK

typedef struct TAG_STACK {
    int capacity;
    int top;
    int *S;
} STACK;
