#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <iostream>

int main(){
    int n = 4;

    // create vertex array
    pVERTEX *V = new pVERTEX[n + 1];
    for (int i = 1; i <= n; i++){
        V[i] = new VERTEX;
    }

    // create graph
    pNODE *ADJ = createGraph(n);

    // manually add edges (directed)
    addEdge(ADJ, 1, 1, 2, 1.0, 1);
    addEdge(ADJ, 2, 1, 3, 4.0, 1);
    addEdge(ADJ, 3, 2, 3, 2.0, 1);
    addEdge(ADJ, 4, 2, 4, 5.0, 1);
    addEdge(ADJ, 5, 3, 4, 1.0, 1);

    std::cout << "=== GRAPH ===\n";
    printGraph(ADJ, n);

    // create heap and stack
    pHEAP heap = createHeap(n);
    pSTACK stack = createStack(n);

    // run Dijkstra
    int source = 1;
    int destination = -1; // full single-source run

    dijkstra(V, ADJ, n, source, destination, heap);

    std::cout << "\n=== RESULTS ===\n";

    for (int i = 1; i <= n; i++){
        std::cout << "Vertex " << i 
                  << " | dist=" << V[i]->key 
                  << " | pi=" << V[i]->pi << "\n";
    }

    std::cout << "\n=== PATH 1 → 4 ===\n";
    printPath(V, 1, 4, stack);

    std::cout << "\n=== LENGTH 1 → 4 ===\n";
    printLength(V, 1, 4);

    // cleanup
    destroyHeap(heap);
    destroyStack(stack);
    destroyGraph(ADJ, n);

    for (int i = 1; i <= n; i++){
        delete V[i];
    }
    delete[] V;

    return 0;
}